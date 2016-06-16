/*
 * Enemy.cpp
 *
 *  Created on: May 30, 2016
 *      Author: nicolas
 */

#include "Enemy.h"

#include <glog/logging.h>
#include <iostream>
#include "../../Box2D/Box2D/Common/b2Math.h"
#include "../../Box2D/Box2D/Dynamics/b2Body.h"
#include "../../Box2D/Box2D/Dynamics/b2Fixture.h"
#include "../../entities.h"
#include "LevelObject.h"
#include "MyLevel.h"
#include "ObjectInfo.h"
#include "Megaman.h"
#include "../../common/CommunicationCodes.h"
#include "../Game.h"
#include "../Event.h"


Enemy::Enemy(b2World* w,Json::Value& json,const b2Vec2& pos,MyLevel* lvl)
:Character(w,json,pos,lvl),
 jumpTime(json["jumpFreq"].asFloat()){
    idle = false;
    hSpeed = 0;
	spriteId=json["id"].asInt();
	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()){
		changeFixtureFilter(f);
	}
	if (json["jumps"].asBool()){
		jumpingSpriteId=json["jumpSpriteId"].asInt();
		createJumpSensor(json["jumpSensor"]);
	}
}

Enemy::~Enemy() {}

/*drops an item, note:chances are at item class*/
ObjectInfo* Enemy::drop() {
	int id=ITEM;
	ObjectInfo* drop=new ObjectInfo(id,body->GetPosition());
	return drop;
}

/*attempts to drop an item and then calls base class kill*/
void Enemy::kill() {
	if(!dead){
		ObjectInfo* dropInfo=drop();
		if(dropInfo!=nullptr){
			level->newObject(dropInfo);
		}
	}
	Character::kill();
}

/*makes sure fixtures collide with corresponding entities*/
void Enemy::changeFixtureFilter(b2Fixture* f) {
	b2Filter filter=f->GetFilterData();
	filter.categoryBits=CHARACTERS;
	filter.maskBits=(BULLETS|BOUNDARIES|SPIKES);
	filter.groupIndex=ENEMY;
	f->SetFilterData(filter);
	f->SetFriction(1);
}

/*calls base class tick, tries to jump, and shoot*/
void Enemy::tick(float time) {
	setAim();
	Character::tick(time);
	executeJump(time);
	shoot();
}

b2Vec2 Enemy::setAim() {
    Megaman* nearest = level->getNearestMegaman(this->getPos());
    b2Vec2 difference = nearest->getPos();
    difference -= this->getPos();
    if (difference.x <= 0){
        if (direction != LEFT){
            direction = LEFT;
            spriteChanged = true;
        }
    } else {
        if (direction != RIGHT){
            direction = RIGHT;
            spriteChanged = true;
        }
    }
    return difference;
}

void Enemy::executeJump(float time) {
    jumpTime.dec(time);
    if (jumpTime.getCurrent() == 0){
        jump();
        jumpTime.maxOut();
    }
}

void Enemy::executeIdle(float time, int idle_time) {
    idle_elapsed = clock();
    if (float(idle_elapsed - idle_begin) / CLOCKS_PER_SEC > idle_time){
        idle = false;
    }
    Character::tick(time);
    shoot();
}

void Enemy::jump() {
    if(canJump){
        b2Vec2 vel = body->GetLinearVelocity();
        vel.y = jSpeed;
        body->SetLinearVelocity(vel);
    }
}
















