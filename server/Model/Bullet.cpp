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

/*watch out bullet not fully initialized. use initialize after*/
Bullet::Bullet(b2World* w,Json::Value& json,const b2Vec2& pos,int id):
LevelObject(w,json,pos,id),level(nullptr){
	body->SetType(b2_dynamicBody);
	body->SetGravityScale(0);
	//	LOG(INFO)<<"bullet:"<<getSpriteId()
	//			<<" created at: "<<(int)pos.x<<(int)pos.y;
}

Bullet::~Bullet() {}

/*collides with object, thus damaging it?*/
void Bullet::collideWith(LevelObject* obj) {
	int objType=obj->getSpriteId()/1000;
	if(objType==9 || objType==1){
		LOG(INFO)<<"bullet hit someone";
		Character* character=(Character*) obj;
		LOG(INFO)<<"cast succesful";
		character->damage(this);
	}
	LOG(INFO)<<"remove me";
	level->remove(this);
	LOG(INFO)<<"done";
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
//	LOG(INFO)<<"bullet initialized with speed: "
//				<<(int)speed.x<<"-"<<(int)speed.y
//				<<" and group bits: "<<groupBits;
	body->SetLinearVelocity(speed);

}

void Bullet::copyCorner(b2Vec2& corner) {
	corner.x=body->GetPosition().x;
	corner.y=body->GetPosition().y;
}
