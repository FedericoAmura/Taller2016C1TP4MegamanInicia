/*
 * Enemy.cpp
 *
 *  Created on: May 30, 2016
 *      Author: nicolas
 */

#include "Enemy.h"

#include <glog/logging.h>
#include "../../Box2D/Box2D/Common/b2Math.h"
#include "../../Box2D/Box2D/Dynamics/b2Body.h"
#include "../../Box2D/Box2D/Dynamics/b2Fixture.h"
#include "../../entities.h"
#include "LevelObject.h"
#include "MyLevel.h"
#include "ObjectInfo.h"
#include "Megaman.h"
#include "../../common/CommunicationCodes.h"
#include "../Game.h"
#include "../Event.h"

Enemy::Enemy(b2World* w,Json::Value& json,const b2Vec2& pos,MyLevel* lvl)
:Character(w,json,pos,lvl),
 jumpTime(json["jumpFreq"].asFloat()){
	spriteId=json["id"].asInt();
	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()){
		changeFixtureFilter(f);
	}
	if(json["jumps"].asBool()){
		jumpingSpriteId=json["jumpSpriteId"].asInt();
		createJumpSensor(json["jumpSensor"]);
	}
}

Enemy::~Enemy() {}

/*drops an item, note:chances are at item class*/
ObjectInfo* Enemy::drop() {
	int id=ITEM;
	ObjectInfo* drop=new ObjectInfo(id,body->GetPosition());
	return drop;
}

/*attempts to drop an item and then calls base class kill*/
void Enemy::kill() {
	if(!dead){
		ObjectInfo* dropInfo=drop();
		if(dropInfo!=nullptr){
			level->newObject(dropInfo);
		}
	}
	Character::kill();
}

/*makes sure fixtures collide with corresponding entities*/
void Enemy::changeFixtureFilter(b2Fixture* f) {
	b2Filter filter=f->GetFilterData();
	filter.categoryBits=CHARACTERS;
	filter.maskBits=(BULLETS|BOUNDARIES|SPIKES);
	filter.groupIndex=ENEMY;
	f->SetFilterData(filter);
	f->SetFriction(1);
}

/*calls base class tick, tries to jump, and shoot*/
void Enemy::tick(float time) {
	Megaman* nearest=level->getNearestMegaman(this->getPos());
	b2Vec2 diference=nearest->getPos();
	diference-=this->getPos();
	if(diference.x<=0){
		if(direction!=LEFT){
			direction=LEFT;
			spriteChanged=true;
		}
	}else{
		if(direction!=RIGHT){
			direction=RIGHT;
			spriteChanged=true;
		}
	}
	Character::tick(time);
	jumpTime.dec(time);
	if(jumpTime.getCurrent()==0){
		jump();
		jumpTime.maxOut();
	}
	shoot();
}

/************************************************************/
FlyingEnemy::FlyingEnemy(b2World* w,
		Json::Value& json,
		const b2Vec2& pos,
		MyLevel* lvl)
:Enemy(w,json,pos,lvl){
	hSpeed=json["HSpeed"].asFloat();
	body->SetGravityScale(0);
}

FlyingEnemy::~FlyingEnemy() {}

/*calls base class tick, and tires to move towards players*/
void FlyingEnemy::tick(float time){
	Enemy::tick(time);
	b2Vec2 speed=body->GetLinearVelocity();;
	if(direction==LEFT)
		speed.x=-hSpeed;
	else
		speed.x=hSpeed;
	body->SetLinearVelocity(speed);
}

bool FlyingEnemy::isJumping() {
	return false;
}
/************************************************************/
Boss::Boss(b2World* w, Json::Value& json, const b2Vec2& pos, MyLevel* lvl)
:Enemy(w,json,pos,lvl),
 lifeChanged(true){}

Boss::~Boss() {}

/*when boss dies the game is won*/
void Boss::kill() {
	level->win();
}

void Boss::redrawForClients(Game* game, MyLevel* level, bool checkChanges) {
	Character::redrawForClients(game,level,checkChanges);
	if(!dead && lifeChanged){
		lifeChanged=false;
		std::stringstream msj;
		int percentage =
				(int) ((((float) (life.getCurrent())) / life.getMax() * 100));
		msj << LIFE_STATUS << " 0 "	<< percentage;
		game->notify(new MessageSent(msj.str(), 0));
	}
}


