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
    void executeJump(float time, float jump_time);
    void executeWalk(float time, b2Vec2& aim);
    void executeAttack(float time);
    virtual void jump();

public:
	Boss(b2World* w, Json::Value& json, const b2Vec2& pos, MyLevel* lvl);
	virtual ~Boss() { }
	virtual void kill();
	virtual void redrawForClients(Game* game, MyLevel* level, bool checkChanges);
    void tick(float time);
};

#endif //MEGAMAN_BOSS_H
