/*
 * Obstacle.h
 *
 *  Created on: May 28, 2016
 *      Author: nicolas
 */

#ifndef SERVER_MODEL_OBSTACLE_H_
#define SERVER_MODEL_OBSTACLE_H_

#include "LevelObject.h"
#include <Box2D/Box2D.h>
#include "../json/json.h"

class Obstacle: public LevelObject {
public:
	Obstacle(b2World* w,Json::Value& json,const b2Vec2& pos,int id);
	virtual ~Obstacle();
	bool changed();
};

class Spikes: public Obstacle{
	void changeFixtureFilter(b2Fixture* f);
public:
	Spikes(b2World* w,Json::Value& json,const b2Vec2& pos,int id);
	virtual ~Spikes();
	void collideWith(LevelObject* obj);
};

#endif /* SERVER_MODEL_OBSTACLE_H_ */
