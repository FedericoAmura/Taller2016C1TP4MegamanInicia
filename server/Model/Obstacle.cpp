/*
 * Obstacle.cpp
 *
 *  Created on: May 28, 2016
 *      Author: nicolas
 */

#include "Obstacle.h"

Obstacle::Obstacle(b2World* w,Json::Value& json,const b2Vec2& pos,int id):
LevelObject(w,json,pos,id){
	body->SetType(b2_staticBody);
}

Obstacle::~Obstacle() {}

bool Obstacle::changed() {
	return false;
}
