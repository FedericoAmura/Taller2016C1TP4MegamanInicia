/*
 * MyLevel.h
 *
 *  Created on: May 21, 2016
 *      Author: nicolas
 */

#ifndef SERVER_MODEL_MYLEVEL_H_
#define SERVER_MODEL_MYLEVEL_H_

#include <map>
#include <queue>
#include <string>
#include <vector>

#include "../../Box2D/Box2D/Common/b2Math.h"
#include "../../Box2D/Box2D/Dynamics/b2World.h"
#include "../../common/Thread.h"
#include "../../json/json.h"
#include "Character.h"
#include "Megaman.h"
#include "MyContactListener.h"
#include "ObjectFactory.h"
#include "Spawner.h"
#include "../Metadata.h"

class BossDoor;
class ObjectInfo;
class Character;
class Megaman;
class Game;

class MyLevel: public Thread{
	b2World world;
	Mutex runningMutex;
	bool running;
	Game* game;
	std::map<int,LevelObject*> objects;
	std::map<int,Megaman*> megamans;
	MyContactListener contactListener;
	ObjectFactory factory;
	b2Vec2 jsonPosToWorldPos(int x, int y);
	void fileToJson(std::string fileName, Json::Value& json);

	LevelObject* boundaries;
	void createBoundaries();

	std::vector<Spawner*> spawners;
	void addSpawner(int id,b2Vec2& pos);
	void spawn();

	std::queue<LevelObject*> toRemove;
	void removeDead();

	void redrawForClient(bool checkChanges=true);

	std::queue<Megaman*> toRespawn;
	void respawnAll();

	std::map<int,Character*> characters;
	void tickAll(float time);

	std::queue<ObjectInfo*> toCreate;
	void createNewObjects();

	void moveScreen();
	bool allMegamansDead();

	void startBossEncounter();

	float stepsPerSecond;
	float worldWidth;
	float worldHeight;
	float windowWidth;
	float windowHeight;
	b2Vec2 windowPos;
	Metadata* metadata;
	int id;

public:
	bool bossEncounter;
	explicit MyLevel(Game* j,std::string lvlFileName, Metadata* metadata,int id);
	virtual ~MyLevel();
	void run();
	void stop();
	bool isRunning();
	void changeKeyState(uint keyState, int client);

	void remove(LevelObject* deadObject);
	void respawn(Megaman* meg);
	LevelObject* createObject(ObjectInfo* info);
	void newObject(ObjectInfo* info);
	bool posInWindow(const b2Vec2& pos);
	std::string posToString(b2Vec2 pos);
	void megamanAtDoor(BossDoor* door);
	void addMegaman(Megaman* newMegaman);
	void removeClient(int clientNumber);
	void addCharacter(Character* newCharacter);
	void addObject(LevelObject* newObject);
	void win();
	Megaman* getNearestMegaman(const b2Vec2& pos);

};

#endif /* SERVER_MODEL_MYLEVEL_H_ */
