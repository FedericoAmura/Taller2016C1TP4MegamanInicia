//
// Created by marcos on 16/06/16.
//

#include <Box2D/Dynamics/b2World.h>
#include "FlyingEnemy.h"
#include "../../json/json.h"
#include "MyLevel.h"
#include "Enemy.h"

#define IDLE_TIME 0.05
#define IDLE_DISTANCE 1
#define ATTACKING_DISTANCE 3

FlyingEnemy::FlyingEnemy(b2World* w,
                         Json::Value& json,
                         const b2Vec2& pos,
                         MyLevel* lvl) : Enemy(w, json, pos, lvl){
    isIdle = false;
    hSpeed = json["HSpeed"].asFloat();
    body->SetGravityScale(0);
}

/*calls base class tick, and tires to move towards players*/
void FlyingEnemy::tick(float time){
    if (isIdle) {
        idle_elapsed = clock();
        if (float(idle_elapsed - idle_begin) / CLOCKS_PER_SEC > IDLE_TIME){
            isIdle = false;
        }
        Character::tick(time);
        shoot();

    } else {
        Megaman* nearest = level->getNearestMegaman(this->getPos());
        b2Vec2 difference = nearest->getPos();
        difference -= this->getPos();
        b2Vec2 speed = body->GetLinearVelocity();
        if (difference.x <= 0){
            if (direction != LEFT){
                direction = LEFT;
                spriteChanged = true;
            }
            speed.x = -hSpeed;
        } else {
            if (direction != RIGHT){
                direction = RIGHT;
                spriteChanged = true;
            }
            speed.x = hSpeed;
        }
        if (abs(difference.x) < IDLE_DISTANCE) {
            isIdle = true;
            idle_begin = clock();
        }
        Character::tick(time);
        body->SetLinearVelocity(speed);
        if (abs(difference.x) < ATTACKING_DISTANCE){
            shoot();
        }
    }
}

bool FlyingEnemy::isJumping() {
    return false;
}