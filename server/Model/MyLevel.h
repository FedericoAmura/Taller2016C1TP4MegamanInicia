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
#include <map>
#include <queue>
#include <vector>

#include "../Thread.h"
#include "LevelObject.h"
#include "MyContactListener.h"
#include "ObjectInfo.h"

class Character;
class Megaman;
class Game;

class MyLevel: public Thread{
	b2World world;
	Mutex runningMutex;
	bool running;
	Game* game;
	std::map<int,LevelObject*> objects;
	Megaman* megaman;
	MyContactListener contactListener;
	std::string posToString(b2Vec2 pos);
	b2Vec2 jsonPosToWorldPos(int x, int y);
	void createBoundaries();
	void fileToJson(std::string fileName, Json::Value& json);

	LevelObject* createObject(int id,b2Vec2& pos,Json::Value config);
	std::queue<LevelObject*> toRemove;
	void removeDead();
	void redrawForClient();
	std::queue<Megaman*> toRespawn;
	void respawnAll();
	std::vector<Character*> characters;
	void tickAll(float time);
	std::queue<ObjectInfo*> toCreate;
	void createNewObjects();

	float stepsPerSecond;
	float hScale;
	float vScale;
	float w_width;
	float w_height;

public:
	explicit MyLevel(Game* j,std::string lvlFileName);
	virtual ~MyLevel();
	void run();
	void stop();
	bool isRunning();
	void moveMegaman(char boton);
	void remove(LevelObject* deadObject);
	void respawn(Megaman* meg);
	void newObject(ObjectInfo* info);
};

#endif /* SERVER_MODEL_MYLEVEL_H_ */
