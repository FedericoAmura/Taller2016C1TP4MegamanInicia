/*
 * Megaman.cpp
 *
 *  Created on: May 27, 2016
 *      Author: nicolas
 */

#include "Megaman.h"
#include "../entities.h"
#include "LevelObject.h"
#include "MyLevel.h"
#include <glog/logging.h>

Megaman::Megaman(b2World* w,Json::Value& json,const b2Vec2& pos,MyLevel* lvl):
LevelObject(w,json,pos,MEGAMAN_IDLE_0),livesRemaining(3),level(lvl),canJump(false){
	spawnPoint=pos;
	body->SetType(b2_dynamicBody);
	body->SetFixedRotation(true);
	body->SetBullet(true);
	hSpeed=json["HSpeed"].asFloat();
	jFactor=json["JFactor"].asFloat();
	//set filters
	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()){
		changeFixtureFilter(f);
	}
	//no jump in air
	Json::Value jSensor=json["jumpSensor"];
	b2PolygonShape polygonShape;
	b2Vec2 center(jSensor["x"].asFloat(),jSensor["y"].asFloat());
	polygonShape.SetAsBox(jSensor["width"].asFloat(),
			jSensor["height"].asFloat(),center,0);//place and size
	b2FixtureDef sensorFixDef;
	sensorFixDef.shape = &polygonShape;
	sensorFixDef.density = 0.01;
	sensorFixDef.isSensor = true;
	sensorFixDef.filter.maskBits=BOUNDARY;//only detects floor (or walls)
	b2Fixture* jumpSensor = body->CreateFixture(&sensorFixDef);
	jumpSensor->SetUserData((void*)JUMPSENSOR);//to recognize sensor
}

Megaman::~Megaman() {}

/*makes sure fixtures collide with corresponding entities*/
void Megaman::changeFixtureFilter(b2Fixture* f) {
	b2Filter filter=f->GetFilterData();
	filter.categoryBits=FRIENDLY;
	filter.maskBits=(ENEMY|BOUNDARY|SPIKES);
	f->SetFilterData(filter);
}

/*jumps, like duh*/
void Megaman::jump() {
	if(canJump){
		b2Vec2 vel = body->GetLinearVelocity();
		vel.y = jFactor * (-world->GetGravity().y); //upwards - don't change x velocity
		body->SetLinearVelocity(vel);
	}
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
		jump();
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
		body->SetLinearVelocity(vel);
		break;
	}
	default: break;
	}
}

/*kill megaman*/
void Megaman::kill() {
	LOG(INFO)<<"megaman murio,vidas restantes: "
			<<livesRemaining;
	if(livesRemaining>=1){
		livesRemaining--;
		level->respawn(this);
	}else{
		level->remove(this);
	}
}

/*warning: do not call from inside world step or contact listener
 * sends megaman to his assigned spawning point*/
void Megaman::spawn() {
	body->SetTransform(spawnPoint,0);
}
