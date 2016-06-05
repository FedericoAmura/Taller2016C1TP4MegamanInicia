/*
 * Items.h
 *
 *  Created on: Jun 5, 2016
 *      Author: nicolas
 */

#ifndef SERVER_MODEL_ITEMS_H_
#define SERVER_MODEL_ITEMS_H_

#include "../../json/json.h"
#include "LevelObject.h"

class b2Fixture;
class MyLevel;

class Item: public LevelObject {
protected:
	bool removed;
	MyLevel* level;
	void changeFixtureFilter(b2Fixture* f);
public:
	Item(b2World* w,Json::Value& json,const b2Vec2& pos,int id,MyLevel* lvl);
	virtual ~Item();
	virtual void collideWith(LevelObject* object);
};

class EnergyItem: public Item{
	uint healAmount;
public:
	EnergyItem(b2World* w,Json::Value& json,const b2Vec2& pos,int id,MyLevel* lvl);
	virtual ~EnergyItem();
	void collideWith(LevelObject* object);
};

class PlasmaItem: public Item{
	uint chargeAmount;
public:
	PlasmaItem(b2World* w,Json::Value& json,const b2Vec2& pos,int id,MyLevel* lvl);
	virtual ~PlasmaItem();
	void collideWith(LevelObject* object);
};

class LifeItem: public Item{
public:
	LifeItem(b2World* w,Json::Value& json,const b2Vec2& pos,int id,MyLevel* lvl);
	virtual ~LifeItem();
	void collideWith(LevelObject* object);
};
#endif /* SERVER_MODEL_ITEMS_H_ */
