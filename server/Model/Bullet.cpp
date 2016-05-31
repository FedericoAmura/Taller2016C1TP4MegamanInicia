/*
 * Bullet.cpp
 *
 *  Created on: May 30, 2016
 *      Author: nicolas
 */

#include "Bullet.h"
#include "LevelObject.h"
#include "Character.h"

/*watch out bullet not fully initialized. use initialize after*/
Bullet::Bullet(b2World* w,Json::Value& json,const b2Vec2& pos,int id):
LevelObject(w,json,pos,id),level(nullptr){}

Bullet::~Bullet() {}

/*collides with object, thus damaging it?*/
void Bullet::collideWith(LevelObject* obj) {
	int objType=obj->getSpriteId()/1000;
	if(objType==9||objType==1){
		Character* character=(Character*) obj;
		character->damage(this);
	}
	level->remove(this);
}

/*use this to finish initialization*/
void Bullet::initialize(uint16 groupBits,b2Vec2& speed,MyLevel* lvl) {
	level=lvl;
	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()){
		b2Filter filter=f->GetFilterData();
		filter.categoryBits=BULLETS;
		filter.maskBits=(CHARACTERS|BOUNDARIES|SPIKES);
		filter.groupIndex=groupBits;
		f->SetFilterData(filter);
	}
	body->SetLinearVelocity(speed);
}
