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

Enemy::Enemy(b2World* w,Json::Value& json,const b2Vec2& pos,MyLevel* lvl):
Character(w,json,pos,lvl),
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

ObjectInfo* Enemy::chooseDrop() {
	int id;
	//todo get chances and choose randomly
	id=BIG_ENERGY;
	ObjectInfo* drop=new ObjectInfo(id,body->GetPosition());
	return drop;
}

void Enemy::kill() {
	if(!dead){
		ObjectInfo* drop=chooseDrop();
		if(drop!=nullptr){
			LOG(INFO)<<"dropped item: "<<drop->getId();
			level->newObject(drop);
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

void Enemy::tick(float time) {
	Character::tick(time);
	jumpTime.dec(time);
	if(jumpTime.getCurrent()==0){
		jump();
		jumpTime.maxOut();
	}
	shoot();
}

FlyingEnemy::FlyingEnemy(b2World* w,
		Json::Value& json,
		const b2Vec2& pos,
		MyLevel* lvl):
Enemy(w,json,pos,lvl){
	body->SetGravityScale(0);
}

FlyingEnemy::~FlyingEnemy() {}

void FlyingEnemy::tick(float time){
	Enemy::tick(time);
	//todo move towards a megaman
}


