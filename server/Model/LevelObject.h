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

 enum _entityCategory {
    BOUNDARY =     0x0001,
    FRIENDLY =     0x0002,
    ENEMY =        0x0004,
  };

class LevelObject {
protected:
	static int uniqueId;
	b2World* world;
	b2Body* body;
	const int objectId;
	int spriteId;
	virtual void addFixture(b2FixtureDef& fDef);

public:
	LevelObject(b2World* w,Json::Value& json,const b2Vec2& pos,int id);
	virtual ~LevelObject();
	const b2Vec2& getPos();
	int getId();
	int getSpriteId();
	virtual bool changed();
	virtual void collideWith(LevelObject* obj);
};

#endif /* SERVER_MODEL_LEVELOBJECT_H_ */
