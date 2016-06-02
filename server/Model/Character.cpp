/*
 * Megaman.cpp
 *
 *  Created on: May 27, 2016
 *      Author: nicolas
 */

#include "Character.h"

#include "../entities.h"
#include "LevelObject.h"
#include "MyLevel.h"
#include <glog/logging.h>
#include "Bullet.h"
#include "Weapon.h"

Character::Character(b2World* w,Json::Value& json,const b2Vec2& pos,MyLevel* lvl):
LevelObject(w,json,pos,MEGAMAN_IDLE_0),
level(lvl),
life(json["life"].asInt()),
canJump(false){
	body->SetType(b2_dynamicBody);
	body->SetFixedRotation(true);
	body->SetBullet(true);
	jFactor=json["JFactor"].asFloat();
	myWeapon= new Weapon(json["weaponId"].asInt(),level,ENEMY);
}

Character::~Character() {
	delete myWeapon;
}

/*creates a jump sensor, to avoid jumping in air*/
void Character::createJumpSensor(Json::Value jSensor){
	//no jump in air
	b2PolygonShape polygonShape;
	b2Vec2 center(jSensor["x"].asFloat(),jSensor["y"].asFloat());
	polygonShape.SetAsBox(jSensor["width"].asFloat(),
			jSensor["height"].asFloat(),center,0);//place and size
	b2FixtureDef sensorFixDef;
	sensorFixDef.shape = &polygonShape;
	sensorFixDef.density = 0.01;
	sensorFixDef.isSensor = true;
	sensorFixDef.filter.maskBits=BOUNDARIES;//only detects floor (or walls)
	b2Fixture* jumpSensor = body->CreateFixture(&sensorFixDef);
	jumpSensor->SetUserData((void*)JUMPSENSOR);//to recognize sensor
}

/*jumps if he can, whithout modifying h velocity*/
void Character::jump() {
	if(canJump){
		b2Vec2 vel = body->GetLinearVelocity();
		//todo change
		vel.y = jFactor * (-world->GetGravity().y); //upwards - don't change x velocity
		body->SetLinearVelocity(vel);
	}
}

/*kills character, removing him from game*/
void Character::kill() {
	level->remove(this);
}

/*informs the weapon of the time step*/
void Character::tick(float time){
	myWeapon->tick(time);
}

/*damages by 1, independent of bullet, redefine for dif behaviour*/
void Character::damage(Bullet* bullet) {
	life.dec(1);
}

/*fires the weapon currently held*/
void Character::shoot() {
	myWeapon->shoot(body->GetPosition());
}
