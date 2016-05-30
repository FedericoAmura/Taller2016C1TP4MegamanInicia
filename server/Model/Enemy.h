/*
 * Enemy.h
 *
 *  Created on: May 30, 2016
 *      Author: nicolas
 */

#ifndef SERVER_MODEL_ENEMY_H_
#define SERVER_MODEL_ENEMY_H_

#include "Character.h"

class Enemy: public Character {
protected:
	void changeFixtureFilter(b2Fixture* f);
public:
	Enemy(b2World* w,Json::Value& json,const b2Vec2& pos,MyLevel* lvl);
	virtual ~Enemy();
	void tick(float time);
};

#endif /* SERVER_MODEL_ENEMY_H_ */
