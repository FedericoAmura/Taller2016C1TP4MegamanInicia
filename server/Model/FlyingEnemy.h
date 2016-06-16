//
// Created by marcos on 16/06/16.
//

#ifndef MEGAMAN_FLYINGENEMY_H
#define MEGAMAN_FLYINGENEMY_H


#include "Enemy.h"

class FlyingEnemy: public Enemy {
	float hSpeed;

public:
	FlyingEnemy(b2World* w, Json::Value& json, const b2Vec2& pos, MyLevel* lvl);
	virtual ~FlyingEnemy() {}
	void tick(float time);
	bool isJumping();
};


#endif //MEGAMAN_FLYINGENEMY_H
