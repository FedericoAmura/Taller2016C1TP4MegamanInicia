/*
 * Megaman.h
 *
 *  Created on: May 27, 2016
 *      Author: nicolas
 */

#ifndef SERVER_MODEL_MEGAMAN_H_
#define SERVER_MODEL_MEGAMAN_H_

#include "LevelObject.h"

class Megaman: public LevelObject {
	float hSpeed;
	float jFactor;
public:
	Megaman(b2World* w,Json::Value& json,const b2Vec2& pos);
	virtual ~Megaman();
	void move(char key);
};

#endif /* SERVER_MODEL_MEGAMAN_H_ */
