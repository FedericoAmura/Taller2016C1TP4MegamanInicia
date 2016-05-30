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
#include <glog/logging.h>

int LevelObject::uniqueId=0;

/*creates a new object,at pos, with its config from file*/
LevelObject::LevelObject(b2World* w,Json::Value& json,const b2Vec2& pos,int id)
:world(w),objectId(uniqueId++),spriteId(id){
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(pos.x,pos.y);
	body = world->CreateBody(&bodyDef);
	body->SetUserData(this);
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
		this->addFixture(fixtureDef);
	}
}

/*adds fixture with normal density, no friction or restitution
 * redefine and call super to make sure fixtures collide with corresponding entities*/
b2Fixture* LevelObject::addFixture(b2FixtureDef& fDef) {
	fDef.density = 1;
	fDef.friction=0;
	fDef.restitution=0;
	return body->CreateFixture(&fDef);
}

/*destroys itself and removes body from world*/
LevelObject::~LevelObject() {
	world->DestroyBody(body);
}

/*returns the position in world coordinates*/
const b2Vec2& LevelObject::getPos() {
	return body->GetPosition();
}

/*returns the unique object id*/
int LevelObject::getId(){
	return objectId;
}

/*returns the object sprite id*/
int LevelObject::getSpriteId() {
	return spriteId;
}

/*returns whether the object has suffered changes*/
bool LevelObject::changed() {
	return body->IsAwake();
}

/*default does nothing, should be redifined in subclass*/
void LevelObject::collideWith(LevelObject* obj) {}
