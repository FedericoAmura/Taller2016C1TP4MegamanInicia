/*
 * Weapom.h
 *
 *  Created on: May 30, 2016
 *      Author: nicolas
 */

#ifndef SERVER_MODEL_WEAPON_H_
#define SERVER_MODEL_WEAPON_H_

#include <Box2D/Box2D.h>
#include "MyLevel.h"
#include "Stat.h"

class Weapon {
	MyLevel* level;
protected:
	int weaponId;
	int16 groupBits;
	Stat<float> cooldown;
	Json::Value getJson();
public:
	Weapon(int id,MyLevel* lvl,int group);
	virtual ~Weapon();
	virtual void shoot(const b2Vec2& pos);
	void setOwner(int16 group);
	void tick(float time);
};

#endif /* SERVER_MODEL_WEAPON_H_ */
