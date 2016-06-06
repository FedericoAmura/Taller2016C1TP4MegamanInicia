/*
 * Bullet.cpp
 *
 *  Created on: May 30, 2016
 *      Author: nicolas
 */

#include "Bullet.h"
#include "LevelObject.h"
#include "Character.h"
#include <glog/logging.h>
#include <iomanip>		//setprecision
#include <iostream>		//fixed

/*watch out bullet not fully initialized. use initialize after*/
Bullet::Bullet(b2World* w,Json::Value& json,const b2Vec2& pos,int id):
LevelObject(w,json,pos,id),
level(nullptr),
removed(false){
	body->SetType(b2_dynamicBody);
	body->SetGravityScale(0);
	body->SetBullet(true);
	damage=json["damage"].asUInt();
	//	LOG(INFO)<<"bullet:"<<getSpriteId()
	//			<<" created at: "<<(int)pos.x<<(int)pos.y;
}

Bullet::~Bullet() {}

/*collides with object, thus damaging it?*/
void Bullet::collideWith(LevelObject* obj) {
	if(!removed){
		int objType=obj->getSpriteId()/1000;
		if(objType==9 || objType==1){
			LOG(INFO)<<"bullet hit someone";
			Character* character=(Character*) obj;
			character->damage(this);
		}
		level->remove(this);
		removed=true;
	}
}

/*use this to finish initialization*/
void Bullet::initialize(int16 groupBits,b2Vec2& speed,MyLevel* lvl) {
	level=lvl;
	body->SetLinearVelocity(speed);
	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()){
		b2Filter filter=f->GetFilterData();
		filter.categoryBits=BULLETS;
		filter.maskBits=(CHARACTERS|BOUNDARIES|SPIKES);
		filter.groupIndex=groupBits;
		f->SetFilterData(filter);
		f->SetDensity(0.001);
	}
//	LOG(INFO)<<std::fixed<<std::setprecision(2)
//			<<"bullet initialized with speed: "
//			<<speed.x<<" "<<speed.y	<<" and group bits: "<<groupBits;
}

void Bullet::copyCorner(b2Vec2& corner) {
	corner.x=body->GetPosition().x +0.45;
	corner.y=body->GetPosition().y -0.45;
}

uint Bullet::getDamage() {
	return damage;
}
