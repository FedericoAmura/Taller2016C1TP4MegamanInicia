/*
 * ObjectFactory.h
 *
 *  Created on: Jun 3, 2016
 *      Author: nicolas
 */

#ifndef SERVER_MODEL_OBJECTFACTORY_H_
#define SERVER_MODEL_OBJECTFACTORY_H_

#include <queue>

#include "ObjectInfo.h"

struct b2Vec2;
class LevelObject;
class b2World;
class MyLevel;

class ObjectFactory {
	b2World* world;
	MyLevel* level;

	std::string idToStr(int id);

public:
	ObjectFactory(b2World* w, MyLevel* lvl);
	virtual ~ObjectFactory();
	LevelObject* createObject(ObjectInfo* info);
};

#endif /* SERVER_MODEL_OBJECTFACTORY_H_ */
