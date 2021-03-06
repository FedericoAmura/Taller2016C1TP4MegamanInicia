/*
 * LevelObject.h
 *
 *  Created on: May 24, 2016
 *      Author: nicolas
 */

#ifndef SERVER_MODEL_LEVELOBJECT_H_
#define SERVER_MODEL_LEVELOBJECT_H_

#include <Box2D/Box2D.h>
#include "../json/json.h"
#include <string>

#define JUMPSENSOR 1

class MyLevel;
class Game;

//todo use namespace to avoid name cluttering
enum _entityCategory {
	BOUNDARIES 	=	0x0001,
	SPIKES 		=	0x0002,
	LADDERS		=	0X0004,
	BULLETS		=	0x0008,
	ITEMS		=	0x0010,
	CHARACTERS	=	0x0020,
};

enum _entityGroups{
	FRIENDLY	= -1,
	ENEMY		= -2,
};

class LevelObject {
protected:
	static int uniqueId;
	b2World* world;
	b2Body* body;
	const int objectId;
	int spriteId;
	b2Fixture* addFixture(b2FixtureDef& fDef);
	void createFixture(Json::Value& jsonShape);
	virtual void copyCorner(b2Vec2& corner);
	std::string posToString(b2Vec2 pos);

public:
	LevelObject(b2World* w,Json::Value& json,const b2Vec2& pos,int id);
	virtual ~LevelObject();
	static void resetIds();
	const b2Vec2& getPos();
	int getId();
	virtual int getSpriteId();
	virtual bool changed();
	virtual void collideWith(LevelObject* obj);
	virtual void stopCollidingWith(LevelObject* obj);
	virtual void registerIn(MyLevel* level);
	virtual void redrawForClients(Game* game,MyLevel* level,bool checkChanges);
};

#endif /* SERVER_MODEL_LEVELOBJECT_H_ */
