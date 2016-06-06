/*
 * Obstacle.cpp
 *
 *  Created on: May 28, 2016
 *      Author: nicolas
 */

#include "Obstacle.h"
#include <Box2D/Box2D.h>
#include <glog/logging.h>
#include "../json/json.h"
#include "Character.h"
#include "LevelObject.h"

Obstacle::Obstacle(b2World* w,Json::Value& json,const b2Vec2& pos,int id):
LevelObject(w,json,pos,id){
	body->SetType(b2_staticBody);
}

Obstacle::~Obstacle() {}

bool Obstacle::changed() {
	return false;
}

/***********************************************************************/

Spikes::Spikes(b2World* w, Json::Value& json, const b2Vec2& pos, int id):
		Obstacle(w,json,pos,id){
	//set filters
	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()){
		changeFixtureFilter(f);
	}
}

Spikes::~Spikes() {}

void Spikes::collideWith(LevelObject* obj) {
	int objType= obj->getSpriteId()/1000;
	if(objType==9||objType==1){
		Character* character= (Character*)obj;
		character->kill();
	}
}

void Spikes::changeFixtureFilter(b2Fixture* f) {
	b2Filter filter=f->GetFilterData();
	filter.categoryBits=SPIKES;
	filter.maskBits=(CHARACTERS|BULLETS);
	f->SetFilterData(filter);
}

/***********************************************************************/

void Ladder::changeFixtureFilter(b2Fixture* f) {
	b2Filter filter=f->GetFilterData();
	filter.categoryBits=LADDERS;
	filter.maskBits=(CHARACTERS);
	filter.groupIndex=ENEMY;
	f->SetFilterData(filter);
}

Ladder::Ladder(b2World* w, Json::Value& json, const b2Vec2& pos, int id):
		Obstacle(w,json,pos,id){
	//set filters
	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()){
		changeFixtureFilter(f);
		f->SetSensor(true);
	}
}

Ladder::~Ladder() {}

void Ladder::collideWith(LevelObject* obj) {
	//I'm supposed to only collide with megamans
	//LOG(INFO)<<"megaman touching ladder";
	Megaman* meg=(Megaman*)obj;
	meg->laddersTouching++;
	meg->checkClimbing();
}

void Ladder::stopCollidingWith(LevelObject* obj) {
	//LOG(INFO)<<"megaman stoped touching ladder";
	Megaman* megaman=(Megaman*)obj;
	if(megaman->laddersTouching>0)//avoid underflow
		megaman->laddersTouching--;
	megaman->checkClimbing();
}

/***********************************************************************/

void BossDoor::changeFixtureFilter(b2Fixture* f) {
	b2Filter filter=f->GetFilterData();
	filter.categoryBits=LADDERS;
	filter.maskBits=(CHARACTERS);
	filter.groupIndex=ENEMY;
	f->SetFilterData(filter);
}

BossDoor::BossDoor(b2World* w,
		Json::Value& json,
		const b2Vec2& pos, int id,
		MyLevel* lvl):
		Obstacle(w,json,pos,id),
		level(lvl){
	//set filters
	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()){
		changeFixtureFilter(f);
		f->SetSensor(true);
	}
}

BossDoor::~BossDoor() {
}

void BossDoor::collideWith(LevelObject* obj) {
	if(megamansTouching.find(obj->getId())==megamansTouching.end())
		megamansTouching[obj->getId()]=obj;
	level->megamanAtDoor(this);
}

void BossDoor::stopCollidingWith(LevelObject* obj) {
	if(megamansTouching.find(obj->getId())!=megamansTouching.end())
		megamansTouching.erase(obj->getId());
}

uint BossDoor::getMegamansTouching() {
	return megamansTouching.size();
}
