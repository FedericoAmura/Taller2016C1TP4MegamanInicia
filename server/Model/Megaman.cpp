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

Megaman::~Megaman() {
	// TODO Auto-generated destructor stub
}

/*makes sure fixtures collide with corresponding entities*/
void Megaman::changeFixtureFilter(b2Fixture* f) {
	b2Filter filter=f->GetFilterData();
	filter.categoryBits=CHARACTERS;
	filter.maskBits=(BOUNDARIES|SPIKES|LADDERS|ITEMS|BULLETS);
	filter.groupIndex=FRIENDLY;
	f->SetFilterData(filter);
}

/*takes key and moves accordingly*/
void Megaman::move(char key){
	switch(key){
	case 'a':{
		b2Vec2 vel = body->GetLinearVelocity();
		vel.x=-hSpeed;
		body->SetLinearVelocity(vel);
		break;
	}
	case 'w':{
		if(checkClimbing()){
			b2Vec2 vel(0,climbSpeed);
			body->SetLinearVelocity(vel);
		}else{
			jump();
		}
		break;
	}
	case 'd':{
		b2Vec2 vel = body->GetLinearVelocity();
		vel.x=hSpeed;
		body->SetLinearVelocity(vel);
		break;
	}
	case 's':{
		b2Vec2 vel = body->GetLinearVelocity();
		vel.x=0;//stop moving sideways
		if(checkClimbing()){
			vel.y=-climbSpeed;
		}
		body->SetLinearVelocity(vel);
		break;
	}
	default: break;
	}
}

/*kills megaman. if he has lives remaining he's queued for respawn
 * else he gets removed*/
void Megaman::kill() {
	LOG(INFO)<<"inmune time left: "<<inmuneTime.getCurrent();
	if(inmuneTime.getCurrent()==0){
		LOG(INFO)<<"megaman murio,vidas restantes: "
				<<livesRemaining;
		inmuneTime.maxOut();
		if(livesRemaining>=1){
			livesRemaining--;
			level->respawn(this);
		}else{
			level->remove(this);
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
	inmuneTime.dec(time);
}
