/*
 * Megaman.h
 *
 *  Created on: May 27, 2016
 *      Author: nicolas
 */

#ifndef SERVER_MODEL_CHARACTER_H_
#define SERVER_MODEL_CHARACTER_H_

#include "LevelObject.h"
#include <Box2D/Box2D.h>

#include "Stat.h"

class Weapon;
class Bullet;
class MyLevel;//forward declaration

enum _direction{
	LEFT= 0,
	RIGHT= 1,
};

class Character: public LevelObject {
protected:
	float jSpeed;
	MyLevel* level;
	Weapon* myWeapon;
	Stat<uint> life;
	bool dead;
	int direction;

	void jump();
	void createJumpSensor(Json::Value jSensor);
	virtual void changeFixtureFilter(b2Fixture* f)=0;
public:
	bool canJump;
	bool hasFlipped;

	Character(b2World* w,Json::Value& json,const b2Vec2& pos,MyLevel* lvl);
	virtual ~Character();
	virtual void kill();
	virtual void tick(float time);//in seconds
	virtual void damage(Bullet* bullet);
	void shoot();
	int getDirection();
	bool isDead();
};

#endif /* SERVER_MODEL_CHARACTER_H_ */
