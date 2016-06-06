/*
 * ObjectInfo.cpp
 *
 *  Created on: May 30, 2016
 *      Author: nicolas
 */

#include "ObjectInfo.h"
#include <Box2D/Box2D.h>

ObjectInfo::ObjectInfo(int id, const b2Vec2& pos):objectId(id),position(pos){}

ObjectInfo::~ObjectInfo() {
	// TODO Auto-generated destructor stub
}

int ObjectInfo::getId() {
	return objectId;
}

const b2Vec2& ObjectInfo::getPos() {
	return position;
}

BulletInfo::BulletInfo(int id, const b2Vec2& pos, b2Vec2& speed,uint16 groupBits):
ObjectInfo(id,pos),speed(speed.x,speed.y),groupBits(groupBits){}

BulletInfo::~BulletInfo() {}

uint16 BulletInfo::getGroupBits() {
	return groupBits;
}

b2Vec2& BulletInfo::getSpeed() {
	return speed;
}
