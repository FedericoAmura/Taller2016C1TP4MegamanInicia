/*
 * Megaman.cpp
 *
 *  Created on: May 27, 2016
 *      Author: nicolas
 */

#include "Character.h"

#include "../entities.h"
#include "LevelObject.h"
#include "MyLevel.h"
#include <glog/logging.h>

Character::Character(b2World* w,Json::Value& json,const b2Vec2& pos,MyLevel* lvl):
LevelObject(w,json,pos,MEGAMAN_IDLE_0),level(lvl),canJump(false){
	body->SetType(b2_dynamicBody);
	body->SetFixedRotation(true);
	body->SetBullet(true);
	jFactor=json["JFactor"].asFloat();
}

Character::~Character() {}

/*creates a jump sensor, to avoid jumping in air*/
void Character::createJumpSensor(Json::Value jSensor){
	//no jump in air
	b2PolygonShape polygonShape;
	b2Vec2 center(jSensor["x"].asFloat(),jSensor["y"].asFloat());
	polygonShape.SetAsBox(jSensor["width"].asFloat(),
			jSensor["height"].asFloat(),center,0);//place and size
	b2FixtureDef sensorFixDef;
	sensorFixDef.shape = &polygonShape;
	sensorFixDef.density = 0.01;
	sensorFixDef.isSensor = true;
	sensorFixDef.filter.maskBits=BOUNDARIES;//only detects floor (or walls)
	b2Fixture* jumpSensor = body->CreateFixture(&sensorFixDef);
	jumpSensor->SetUserData((void*)JUMPSENSOR);//to recognize sensor
}

/*jumps if he can, whithout modifying h velocity*/
void Character::jump() {
	if(canJump){
		b2Vec2 vel = body->GetLinearVelocity();
		vel.y = jFactor * (-world->GetGravity().y); //upwards - don't change x velocity
		body->SetLinearVelocity(vel);
	}
}

/*kills character, removing him from game*/
void Character::kill() {
	level->remove(this);
}


