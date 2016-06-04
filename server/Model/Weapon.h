/*
 * Weapom.h
 *
 *  Created on: May 30, 2016
 *      Author: nicolas
 */

#ifndef SERVER_MODEL_WEAPON_H_
#define SERVER_MODEL_WEAPON_H_

#include <Box2D/Common/b2Settings.h>
#include "../../json/json.h"

#include "Stat.h"
#include "MyLevel.h"

struct b2Vec2;

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
	virtual void shoot(const b2Vec2& pos,int direction);
	void setOwner(int16 group);
	void tick(float time);
};

#endif /* SERVER_MODEL_WEAPON_H_ */
