/*
 * Megaman.cpp
 *
 *  Created on: May 27, 2016
 *      Author: nicolas
 */

#include "Megaman.h"
#include "../entities.h"
#include "LevelObject.h"

Megaman::Megaman(b2World* w,Json::Value& json,const b2Vec2& pos):
LevelObject(w,json,pos,MEGAMAN),canJump(false){
	body->SetType(b2_dynamicBody);
	body->SetFixedRotation(true);
	body->SetBullet(true);
	hSpeed=json["HSpeed"].asFloat();
	jFactor=json["JFactor"].asFloat();
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

/*makes sure fixtures collide with enemies and boundaries only*/
void Megaman::addFixture(b2FixtureDef& fDef) {
	fDef.filter.categoryBits=FRIENDLY;
	fDef.filter.maskBits=(ENEMY|BOUNDARY);
	LevelObject::addFixture(fDef);
}

void Megaman::jump() {
	if(canJump){
		b2Vec2 vel = body->GetLinearVelocity();
		vel.y = jFactor * (-world->GetGravity().y); //upwards - don't change x velocity
		body->SetLinearVelocity(vel);
	}
}

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
