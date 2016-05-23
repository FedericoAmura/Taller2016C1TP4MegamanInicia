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

enum _moveState {
    MS_STOP,
    MS_LEFT,
    MS_RIGHT,
  };

class MyLevel: public Thread, public b2ContactListener {
	b2World world;
	Mutex runningMutex;
	bool running;
	Game* game;
	b2Body* megaman;
	std::string posToString(b2Vec2 pos);

public:
	explicit MyLevel(Game* j);
	virtual ~MyLevel();
	void run();
	void stop();
	bool isRunning();
	void moveMegaman(char boton);
	b2Vec2 getPosMegaman();
};

#endif /* SERVER_MODEL_MYLEVEL_H_ */
