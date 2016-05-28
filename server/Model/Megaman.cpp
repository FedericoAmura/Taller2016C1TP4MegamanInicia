/*
 * Megaman.cpp
 *
 *  Created on: May 27, 2016
 *      Author: nicolas
 */

#include "Megaman.h"
#include "../entities.h"

Megaman::Megaman(b2World* w,Json::Value& json,const b2Vec2& pos):
LevelObject(w,json,pos,MEGAMAN){
	body->SetType(b2_dynamicBody);
	body->SetFixedRotation(true);
	body->SetBullet(true);
	hSpeed=json["HSpeed"].asFloat();
	jFactor=json["JFactor"].asFloat();
}

Megaman::~Megaman() {}

void Megaman::move(char key){
	switch(key){
	case 'a':{
		b2Vec2 vel = body->GetLinearVelocity();
		vel.x=-hSpeed;
		body->SetLinearVelocity(vel);
		break;
	}
	case 'w':{
		b2Vec2 vel = body->GetLinearVelocity();

		vel.y =jFactor* (-world->GetGravity().y);//upwards - don't change x velocity
		body->SetLinearVelocity( vel );
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
