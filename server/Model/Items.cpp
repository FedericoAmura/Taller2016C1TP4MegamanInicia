/*
 * Items.cpp
 *
 *  Created on: Jun 5, 2016
 *      Author: nicolas
 */

#include "Items.h"

#include <glog/logging.h>
#include <Box2D/Box2D.h>
#include "Megaman.h"
#include "MyLevel.h"
#include "LevelObject.h"

Item::Item(b2World* w,
		Json::Value& json,
		const b2Vec2& pos, int id,
		MyLevel* lvl):
		LevelObject(w,json,pos,id),
		removed(false),
		level(lvl){
	body->SetType(b2_dynamicBody);
	//set filters
	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()){
		changeFixtureFilter(f);
	}
}

Item::~Item(){}

void Item::changeFixtureFilter(b2Fixture* f) {
	b2Filter filter=f->GetFilterData();
	filter.categoryBits=ITEMS;
	filter.maskBits=(BOUNDARIES|CHARACTERS);
	filter.groupIndex=ENEMY;//wont collide with enemies
	f->SetFilterData(filter);
}

/*destroy me after collision, but only once*/
void Item::collideWith(LevelObject* object) {
	int objectType= object->getSpriteId()/1000;
	if(!removed && objectType!=4 && objectType!=0){//not boundaries
		level->remove(this);
		removed=true;
	}
}

EnergyItem::EnergyItem(b2World* w,
		Json::Value& json,
		const b2Vec2& pos, int id,
		MyLevel* lvl):
						Item(w,json,pos,id,lvl)	{
	healAmount=json["healAmount"].asUInt();
}

EnergyItem::~EnergyItem() {}

/*heal megaman then destroy this*/
void EnergyItem::collideWith(LevelObject* object) {
	int objectType= object->getSpriteId()/1000;
	if(!removed && objectType!=4 && objectType!=0){//not boundaries
		Megaman* megaman= (Megaman*) object;//I should only collide with megaman
		megaman->heal(healAmount);
		Item::collideWith(object);
	}
}

PlasmaItem::PlasmaItem(b2World* w,
		Json::Value& json,
		const b2Vec2& pos, int id,
		MyLevel* lvl)
:Item(w,json,pos,id,level){
	chargeAmount=json["chargeAmount"].asUInt();
}

PlasmaItem::~PlasmaItem() {}

/*charge megaman then destroy this*/
void PlasmaItem::collideWith(LevelObject* object) {
	int objectType= object->getSpriteId()/1000;
	if(!removed && objectType!=4 && objectType!=0){//not boundaries
		Megaman* megaman= (Megaman*) object;//I should only collide with megaman
		megaman->charge(chargeAmount);
		Item::collideWith(object);
	}
}

LifeItem::LifeItem(b2World* w,
		Json::Value& json,
		const b2Vec2& pos, int id,
		MyLevel* lvl)
:Item(w,json,pos,id,level){}

LifeItem::~LifeItem() {}

void LifeItem::collideWith(LevelObject* object) {
	int objectType= object->getSpriteId()/1000;
	if(!removed && objectType!=4 && objectType!=0){//not boundaries
		//Megaman* megaman= (Megaman*) object;//I should only collide with megaman
		//todo add life
		Item::collideWith(object);
	}
}