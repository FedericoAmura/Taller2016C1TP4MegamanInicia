/*
 * Obstacle.cpp
 *
 *  Created on: May 28, 2016
 *      Author: nicolas
 */

#include "Obstacle.h"
#include <Box2D/Box2D.h>
#include "../json/json.h"
#include "LevelObject.h"
#include "Megaman.h"

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
	Megaman* megaman= (Megaman*)obj;
	megaman->kill();
}

void Spikes::changeFixtureFilter(b2Fixture* f) {
	b2Filter filter=f->GetFilterData();
	filter.categoryBits=SPIKES;
	filter.maskBits=(ENEMY|FRIENDLY);
	f->SetFilterData(filter);
}
