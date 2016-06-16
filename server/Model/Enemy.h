/*
 * Enemy.h
 *
 *  Created on: May 30, 2016
 *      Author: nicolas
 */

#ifndef SERVER_MODEL_ENEMY_H_
#define SERVER_MODEL_ENEMY_H_

#include "../../json/json.h"
#include "Character.h"
#include "Stat.h"

class b2Fixture;
class ObjectInfo;
class Game;
class MyLevel;

class Enemy: public Character {
protected:
	Stat<float> jumpTime;
	void changeFixtureFilter(b2Fixture* f);
	ObjectInfo* drop();

public:
	Enemy(b2World* w, Json::Value& json, const b2Vec2& pos, MyLevel* lvl);
	virtual ~Enemy();
	virtual void tick(float time);
	virtual void kill();
};

#endif /* SERVER_MODEL_ENEMY_H_ */
