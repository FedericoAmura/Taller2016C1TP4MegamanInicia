/*
 * MyLevel.h
 *
 *  Created on: May 21, 2016
 *      Author: nicolas
 */

#ifndef SERVER_MODEL_MYLEVEL_H_
#define SERVER_MODEL_MYLEVEL_H_

#include <Box2D/Box2D.h>
#include <string>

#include "../Thread.h"

class Game;

class MyLevel: public Thread, public b2ContactListener {
	b2World world;
	Mutex runningMutex;
	bool running;
	Game* game;
	b2Body* megaman;
	std::string posToString(b2Vec2 pos);
	float stepsPerSecond;
	float scale;
	float w_width;
	float w_height;

public:
	explicit MyLevel(Game* j,std::string lvlFileName);
	virtual ~MyLevel();
	void run();
	void stop();
	bool isRunning();
	void moveMegaman(char boton);
	b2Vec2 getPosMegaman();
};

#endif /* SERVER_MODEL_MYLEVEL_H_ */
