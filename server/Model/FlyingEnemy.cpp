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
    hSpeed = json["HSpeed"].asFloat();
    body->SetGravityScale(0);
}

/*calls base class tick, and tires to move towards players*/
void FlyingEnemy::tick(float time){
    if (idle) {
        executeIdle(time, IDLE_TIME);
    } else {
        b2Vec2 speed = body->GetLinearVelocity();
        speed.x = hSpeed;
        if (direction == LEFT) speed = -speed;
        b2Vec2 aim = setAim();
        if (abs(aim.x) < IDLE_DISTANCE) {
            idle = true;
            idle_begin = clock();
        }
        Character::tick(time);
        body->SetLinearVelocity(speed);
        if (abs(aim.x) < ATTACKING_DISTANCE){
            shoot();
        }
    }
}

bool FlyingEnemy::isJumping() {
    return false;
}