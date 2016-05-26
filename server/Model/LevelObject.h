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

class LevelObject {
	b2World* world;
	b2Body* body;
public:
	LevelObject(b2World* w,Json::Value& json,const b2Vec2& pos);
	virtual ~LevelObject();
	void move(char key);
	const b2Vec2& getPos();
};

#endif /* SERVER_MODEL_LEVELOBJECT_H_ */
