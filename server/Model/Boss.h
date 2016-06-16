//
// Created by marcos on 16/06/16.
//

#ifndef MEGAMAN_BOSS_H
#define MEGAMAN_BOSS_H

#include "MyLevel.h"
#include "Enemy.h"

class Boss: public Enemy {
	bool lifeChanged;
	float hSpeed;

public:
	Boss(b2World* w, Json::Value& json, const b2Vec2& pos, MyLevel* lvl);
	virtual ~Boss() { }
	virtual void kill();
	virtual void redrawForClients(Game* game, MyLevel* level, bool checkChanges);
	//void jump();
	//void tick(float time);
};

#endif //MEGAMAN_BOSS_H
