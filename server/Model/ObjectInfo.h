/*
 * ObjectInfo.h
 *
 *  Created on: May 30, 2016
 *      Author: nicolas
 */

#ifndef SERVER_MODEL_OBJECTINFO_H_
#define SERVER_MODEL_OBJECTINFO_H_

#include <Box2D/Box2D.h>

class ObjectInfo {
	int objectId;
	const b2Vec2& position;

public:
	ObjectInfo(int id,const b2Vec2& pos);
	virtual ~ObjectInfo();
	int getId();
	const b2Vec2& getPos();

};

class BulletInfo: public ObjectInfo{
	b2Vec2& speed;
	uint16 groupBits;
public:
	BulletInfo(int id,const b2Vec2& pos,b2Vec2& speed, uint16 groupBits);
	virtual ~BulletInfo();
	uint16 getGroupBits();
	b2Vec2& getSpeed();
};
#endif /* SERVER_MODEL_OBJECTINFO_H_ */
