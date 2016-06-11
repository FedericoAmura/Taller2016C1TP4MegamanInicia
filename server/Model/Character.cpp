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
#include "../common/CommunicationCodes.h"
#include "../Game.h"

Character::Character(b2World* w,Json::Value& json,const b2Vec2& pos,MyLevel* lvl):
LevelObject(w,json,pos,MEGAMAN_IDLE_0),
level(lvl),
life(json["life"].asInt()),
dead(false),
direction(LEFT),
hasFlipped(false),
canJump(false){
	body->SetType(b2_dynamicBody);
	body->SetFixedRotation(true);
	body->SetBullet(true);
	jSpeed=json["JSpeed"].asFloat();
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
		vel.y = jSpeed; //upwards - don't change x velocity
		body->SetLinearVelocity(vel);
	}
}

/*kills character, removing him from game*/
void Character::kill() {
	if(!dead){
		dead=true;
		level->remove(this);
	}
}

/*informs the weapon of the time step*/
void Character::tick(float time){
	myWeapon->tick(time);
}

/*damages by 1, independent of bullet, redefine for dif behaviour*/
void Character::damage(Bullet* bullet) {
	life.dec(bullet->getDamage());
	LOG(INFO)<<"id: "<<this->getId()<<" life left "<<life.getCurrent();
	if(life.getCurrent()==0)
		this->kill();
}

/*fires the weapon currently held*/
void Character::shoot() {
	myWeapon->shoot(body->GetPosition(),direction);
}

int Character::getDirection() {
	return direction;
}

bool Character::isDead() {
	return dead;
}

void Character::registerIn(MyLevel* level) {
	level->addCharacter(this);
}

void Character::redrawForClients(Game* game, MyLevel* level,
		bool checkChanges) {
	LevelObject::redrawForClients(game,level,checkChanges);
	if(hasFlipped){
		hasFlipped=false;
		std::stringstream msj;
		msj<<REDRAW<<" "<<getId()<<" "<<getSpriteId()<<" "<<direction;
		game->notify(new MessageSent(msj.str(),0));
	}
}
