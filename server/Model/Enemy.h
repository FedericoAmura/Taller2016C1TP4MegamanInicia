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

class FlyingEnemy: public Enemy {
	float hSpeed;
    bool isIdle;
    clock_t idle_begin;
    clock_t idle_elapsed;
public:
	FlyingEnemy(b2World* w, Json::Value& json, const b2Vec2& pos, MyLevel* lvl);
	virtual ~FlyingEnemy() {}
	void tick(float time);
	bool isJumping();
};

class Boss: public Enemy {
	bool lifeChanged;
public:
	Boss(b2World* w, Json::Value& json, const b2Vec2& pos, MyLevel* lvl);
	virtual ~Boss() {}
	virtual void kill();
	virtual void redrawForClients(Game* game, MyLevel* level, bool checkChanges);
};
#endif /* SERVER_MODEL_ENEMY_H_ */
