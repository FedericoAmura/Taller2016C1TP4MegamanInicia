/*
 * Megaman.h
 *
 *  Created on: May 27, 2016
 *      Author: nicolas
 */

#ifndef SERVER_MODEL_MEGAMAN_H_
#define SERVER_MODEL_MEGAMAN_H_

#include "LevelObject.h"
#include <Box2D/Box2D.h>

class MyLevel;//forward declaration

class Megaman: public LevelObject {
	float hSpeed;
	uint livesRemaining;
	b2Vec2 spawnPoint;
	void changeFixtureFilter(b2Fixture* f);
protected:
	float jFactor;
	MyLevel* level;
	void jump();
public:
	bool canJump;
	Megaman(b2World* w,Json::Value& json,const b2Vec2& pos,MyLevel* lvl);
	virtual ~Megaman();
	void move(char key);
	void kill();
	void spawn();
};

#endif /* SERVER_MODEL_MEGAMAN_H_ */
