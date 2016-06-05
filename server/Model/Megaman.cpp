/*
 * Megaman.cpp
 *
 *  Created on: May 30, 2016
 *      Author: nicolas
 */

#include "Megaman.h"
#include "Character.h"
#include "../entities.h"
#include <glog/logging.h>
#include "MyLevel.h"
#include "Weapon.h"
#include "../common/MegamanBeginsConstants.h"

Megaman::Megaman(b2World* w,Json::Value& json,const b2Vec2& pos,MyLevel* lvl):
Character(w,json,pos,lvl),
hSpeed(json["HSpeed"].asFloat()),
climbSpeed(json["ClimbSpeed"].asFloat()),
livesRemaining(3),
spawnPoint(pos),
inmuneTime(json["inmuneTime"].asFloat()),
laddersTouching(0){
	//set filters
	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()){
		changeFixtureFilter(f);
	}
	createJumpSensor(json["jumpSensor"]);
	myWeapon->setOwner(FRIENDLY);
}

Megaman::~Megaman() {}

/*makes sure fixtures collide with corresponding entities*/
void Megaman::changeFixtureFilter(b2Fixture* f) {
	b2Filter filter=f->GetFilterData();
	filter.categoryBits=CHARACTERS;
	filter.maskBits=(BOUNDARIES|SPIKES|LADDERS|ITEMS|BULLETS);
	filter.groupIndex=FRIENDLY;
	f->SetFilterData(filter);
	f->SetFriction(0);
}

/*moves according to new key state*/
void Megaman::changeKeyState(uint keyState){
	b2Vec2 vel = body->GetLinearVelocity();
	bool up,down,left,right,climbing;
	up=keyState & KEY_UP_ID;
	down=keyState & KEY_DOWN_ID;
	left=keyState & KEY_LEFT_ID;
	right=keyState & KEY_RIGHT_ID;
	climbing=checkClimbing();

	if(down){
		if(climbing)
			vel.y=-climbSpeed;
	}else{
		if(climbing && !up)
			vel.y=0;
	}
	if(up){
		if(climbing){
			vel.y=climbSpeed;
		}else{
			jump();
			vel.y=body->GetLinearVelocity().y;
		}
	}else{
		if(climbing && !down)
			vel.y=0;
	}

	if(left){
		vel.x=-hSpeed;
		if(direction!=LEFT){
			direction=LEFT;
			hasFlipped=true;
		}
	}else{
		if(!right)
			vel.x=0;
	}
	if(right){
		vel.x=hSpeed;
		if(direction!=RIGHT){
			direction=RIGHT;
			hasFlipped=true;
		}
	}else{
		if(!left)
			vel.x=0;
	}
	body->SetLinearVelocity(vel);
	if(keyState & KEY_SPACE_ID)
		shoot();
}

/*kills megaman. if he has lives remaining he's queued for respawn
 * else he gets removed*/
void Megaman::kill() {
	//LOG(INFO)<<"inmune time left: "<<inmuneTime.getCurrent();
	if(inmuneTime.getCurrent()==0 && !dead){
		LOG(INFO)<<"megaman murio,vidas restantes: "
				<<livesRemaining;
		inmuneTime.maxOut();
		if(livesRemaining>=1){
			livesRemaining--;
			level->respawn(this);
			dead=false;
		}else{
			level->remove(this);
			dead=true;
		}
	}
}

/*warning: do not call from inside world step or contact listener
 * sends megaman to his assigned spawning point*/
void Megaman::spawn() {
	body->SetTransform(spawnPoint,0);
}

bool Megaman::checkClimbing(){
	if (laddersTouching >0){
		body->SetGravityScale(0.0);
		if(laddersTouching==1){
			b2Vec2 vel =body->GetLinearVelocity();
			vel.y=0;
			body->SetLinearVelocity(vel);
		}
		return true;
	}else{
		body->SetGravityScale(1.0);
		return false;
	}
}

void Megaman::tick(float time) {
	Character::tick(time);
	inmuneTime.dec(time);
}
