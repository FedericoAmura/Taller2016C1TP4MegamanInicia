/*
 * Enemy.cpp
 *
 *  Created on: May 30, 2016
 *      Author: nicolas
 */

#include "Enemy.h"

Enemy::Enemy(b2World* w,Json::Value& json,const b2Vec2& pos,MyLevel* lvl):
Character(w,json,pos,lvl){
	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()){
		changeFixtureFilter(f);
	}
	createJumpSensor(json["jumpSensor"]);
}

Enemy::~Enemy() {
	// TODO Auto-generated destructor stub
}

/*makes sure fixtures collide with corresponding entities*/
void Enemy::changeFixtureFilter(b2Fixture* f) {
	b2Filter filter=f->GetFilterData();
	filter.categoryBits=CHARACTERS;
	filter.maskBits=(BULLETS|BOUNDARIES|SPIKES);
	filter.groupIndex=ENEMY;
	f->SetFilterData(filter);
}
