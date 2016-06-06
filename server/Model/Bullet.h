/*
 * Bullet.h
 *
 *  Created on: May 30, 2016
 *      Author: nicolas
 */

#ifndef SERVER_MODEL_BULLET_H_
#define SERVER_MODEL_BULLET_H_

#include "LevelObject.h"
#include <Box2D/Box2D.h>
#include "../json/json.h"
#include "Weapon.h"

class Bullet: public LevelObject {
	MyLevel* level;
	bool removed;
	uint damage;
public:
	Bullet(b2World* w,Json::Value& json,const b2Vec2& pos,int id);
	virtual ~Bullet();
	void collideWith(LevelObject* obj);
	void initialize(int16 groupBits, b2Vec2& speed, MyLevel* lvl);
	virtual void copyCorner(b2Vec2& corner);
	uint getDamage();
};

#endif /* SERVER_MODEL_BULLET_H_ */
