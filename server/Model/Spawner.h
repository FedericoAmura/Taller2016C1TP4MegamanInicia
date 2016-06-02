/*
 * Spawner.h
 *
 *  Created on: Jun 2, 2016
 *      Author: nicolas
 */

#ifndef SERVER_MODEL_SPAWNER_H_
#define SERVER_MODEL_SPAWNER_H_

#include <Box2D/Box2D.h>

class MyLevel;

class Spawner {
	int id;
	b2Vec2 pos;
	MyLevel* level;
	bool spawned;
public:
	Spawner(int id,b2Vec2& pos, MyLevel* lvl);
	virtual ~Spawner();
	void spawn();
	void spawnedFalse();
};

#endif /* SERVER_MODEL_SPAWNER_H_ */
