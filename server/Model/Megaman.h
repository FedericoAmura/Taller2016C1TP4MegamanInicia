/*
 * Megaman.h
 *
 *  Created on: May 30, 2016
 *      Author: nicolas
 */

#ifndef SERVER_MODEL_MEGAMAN_H_
#define SERVER_MODEL_MEGAMAN_H_

#include "Character.h"
#include "Stat.h"

class Megaman: public Character {
	float hSpeed;
	float climbSpeed;
	uint livesRemaining;
	b2Vec2 spawnPoint;
	Stat<float> inmuneTime;//seconds

	void changeFixtureFilter(b2Fixture* f);

public:
	uint laddersTouching;

	Megaman(b2World* w,Json::Value& json,const b2Vec2& pos,MyLevel* lvl);
	virtual ~Megaman();
	void kill();
	void spawn();
	bool checkClimbing();
	void tick(float time);
	void changeKeyState(uint keyState);
};

#endif /* SERVER_MODEL_MEGAMAN_H_ */
