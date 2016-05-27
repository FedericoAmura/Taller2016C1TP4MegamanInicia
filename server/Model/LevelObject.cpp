/*
 * LevelObject.cpp
 *
 *  Created on: May 24, 2016
 *      Author: nicolas
 */

#include "LevelObject.h"
#include <Box2D/Box2D.h>
#include "../json/json.h"
#include <string>

int LevelObject::uniqueId=0;

LevelObject::LevelObject(b2World* w,Json::Value& json,const b2Vec2& pos,int id)
:world(w),objectId(uniqueId++),spriteId(id){
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x,pos.y);
	bodyDef.fixedRotation=true;
	bodyDef.bullet = true;
	body = world->CreateBody(&bodyDef);
	//shape
	b2PolygonShape shape;
	Json::Value shapes=json["shapes"];
	Json::ValueIterator it=shapes.begin();
	for(; it!=shapes.end(); it++){
		shape.SetAsBox((*it)["width"].asFloat(),(*it)["height"].asFloat(),
				b2Vec2((*it)["X"].asFloat(),(*it)["Y"].asFloat()),0);
		//fixture
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1;
		fixtureDef.friction=0;
		fixtureDef.restitution=0;
		body->CreateFixture(&fixtureDef);
	}
}

LevelObject::~LevelObject() {
	// TODO Auto-generated destructor stub
}

void LevelObject::move(char key){
	switch(key){
	case 'a':{
		b2Vec2 vel = body->GetLinearVelocity();
		vel.x=-10;
		body->SetLinearVelocity(vel);
		break;
	}
	case 'w':{
		b2Vec2 vel = body->GetLinearVelocity();

		vel.y =0.50* (-world->GetGravity().y);//upwards - don't change x velocity
		body->SetLinearVelocity( vel );
		break;
	}
	case 'd':{
		b2Vec2 vel = body->GetLinearVelocity();
		vel.x=10;
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

const b2Vec2& LevelObject::getPos() {
	return body->GetPosition();
}

int LevelObject::getId(){
	return objectId;
}

int LevelObject::getSpriteId() {
	return spriteId;
}
