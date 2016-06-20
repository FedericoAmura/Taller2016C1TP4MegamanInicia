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

class Game;
class Weapon;
class Bullet;
class MyLevel;//forward declaration

enum _direction{
	LEFT = 0,
	RIGHT = 1,
};

class Character: public LevelObject {
protected:
	float jSpeed;
	MyLevel* level;
	Weapon* myWeapon;
	Stat<int> life;
	bool dead;
	int direction;
	bool spriteChanged;
	bool wasJumping;
	int jumpingSpriteId;
	virtual bool isJumping();
	void jump();

	void createJumpSensor(Json::Value jSensor);
	virtual void changeFixtureFilter(b2Fixture* f)=0;
public:
	bool canJump;
	uint surfacesTouching;

	Character(b2World* w,Json::Value& json,const b2Vec2& pos,MyLevel* lvl);
	virtual ~Character();
	virtual void kill();
	virtual void tick(float time);//in seconds
	virtual void damage(Bullet* bullet);
	virtual void damage(int how_much);
	void shoot();
	int getDirection();//todo check and remove if unneccesary
	bool isDead();
	virtual void registerIn(MyLevel* level);
	virtual void redrawForClients(Game* game,MyLevel* level,bool checkChanges);
	virtual int getSpriteId();
};

#endif /* SERVER_MODEL_CHARACTER_H_ */
