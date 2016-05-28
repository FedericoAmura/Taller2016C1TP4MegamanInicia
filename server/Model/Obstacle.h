/*
 * Obstacle.h
 *
 *  Created on: May 28, 2016
 *      Author: nicolas
 */

#ifndef SERVER_MODEL_OBSTACLE_H_
#define SERVER_MODEL_OBSTACLE_H_

#include "LevelObject.h"

class Obstacle: public LevelObject {
public:
	Obstacle(b2World* w,Json::Value& json,const b2Vec2& pos,int id);
	virtual ~Obstacle();
	bool changed();
};

#endif /* SERVER_MODEL_OBSTACLE_H_ */
