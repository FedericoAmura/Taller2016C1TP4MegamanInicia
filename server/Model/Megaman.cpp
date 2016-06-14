/*
 * Megaman.cpp
 *
 *  Created on: May 30, 2016
 *      Author: nicolas
 */

#include "Megaman.h"
#include "Character.h"
#include "../../entities.h"
#include <glog/logging.h>
#include "MyLevel.h"
#include "Weapon.h"
#include "../../common/MegamanBeginsConstants.h"
#include "../../common/CommunicationCodes.h"
#include "../Game.h"
#include "../Event.h"

Megaman::Megaman(b2World* w,Json::Value& json,const b2Vec2& pos,MyLevel* lvl):
Character(w,json,pos,lvl),
hSpeed(json["HSpeed"].asFloat()),
climbSpeed(json["ClimbSpeed"].asFloat()),
clientData(nullptr),
spawnPoint(pos),
inmuneTime(json["inmuneTime"].asFloat()),
wasClimbing(false),
laddersTouching(0){
	//set filters
	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()){
		changeFixtureFilter(f);
	}
	jumpingSpriteId=json["jumpSpriteId"].asInt();
	createJumpSensor(json["jumpSensor"]);
	climbingSpriteId=json["climbSpriteId"].asInt();
	myWeapon->setOwner(FRIENDLY);
}

Megaman::~Megaman() {}

/*makes sure fixtures collide with corresponding entities*/
void Megaman::changeFixtureFilter(b2Fixture* f) {
	b2Filter filter=f->GetFilterData();
	filter.categoryBits=CHARACTERS;
	filter.maskBits=(BOUNDARIES|SPIKES|LADDERS|ITEMS|BULLETS);
	filter.groupIndex=FRIENDLY;
	f->SetFilterData(filter);
	f->SetFriction(0);
}

/*moves according to new key state*/
void Megaman::changeKeyState(uint keyState){
	b2Vec2 vel = body->GetLinearVelocity();
	bool up,down,left,right,climbing;
	up=keyState & KEY_UP_ID;
	down=keyState & KEY_DOWN_ID;
	left=keyState & KEY_LEFT_ID;
	right=keyState & KEY_RIGHT_ID;
	climbing=checkClimbing();

	if(down){
		if(climbing)
			vel.y=-climbSpeed;
	}else{
		if(climbing && !up)
			vel.y=0;
	}
	if(up){
		if(climbing){
			vel.y=climbSpeed;
		}else{
			jump();
			vel.y=body->GetLinearVelocity().y;
		}
	}else{
		if(climbing && !down)
			vel.y=0;
	}

	if(left){
		vel.x=-hSpeed;
		if(direction!=LEFT){
			direction=LEFT;
			spriteChanged=true;
		}
	}else{
		if(!right)
			vel.x=0;
	}
	if(right){
		vel.x=hSpeed;
		if(direction!=RIGHT){
			direction=RIGHT;
			spriteChanged=true;
		}
	}else{
		if(!left)
			vel.x=0;
	}
	body->SetLinearVelocity(vel);
	if(keyState & KEY_SPACE_ID)
		shoot();
}

/*kills megaman. if he has lives remaining he's queued for respawn
 * else he gets removed*/
void Megaman::kill() {
	//LOG(INFO)<<"inmune time left: "<<inmuneTime.getCurrent();
	if(inmuneTime.getCurrent()==0 && !dead && clientData){
		inmuneTime.maxOut();
		if(clientData->getLives().getCurrent()>=1){
			clientData->getLives().dec(1);
			level->respawn(this);
			dead=true;
		}else{
			dead=true;
		}
		std::stringstream killMsg;
		killMsg<<KILL<<" "<<getId();
		clientData->getGame()->notify(new MessageSent(killMsg.str(),0));
		LOG(INFO)<<"megaman murio,vidas restantes: "
				<<clientData->getLives().getCurrent();
	}
}

/*warning: do not call from inside world step or contact listener
 * sends megaman to his assigned spawning point*/
void Megaman::spawn() {
	if(clientData->getLives().getCurrent()>0 || !dead){
		dead=false;
		body->SetTransform(spawnPoint,0);
	}
}

/*	returns true if he is climbing, false if not.
 * also handles vertical motion if he is climbing*/
bool Megaman::checkClimbing(){
	if(!wasClimbing){
		if (laddersTouching >0){
			body->SetGravityScale(0.0);
			if(laddersTouching==1){
				b2Vec2 vel =body->GetLinearVelocity();
				vel.y=0;
				body->SetLinearVelocity(vel);
			}
			return true;
		}else{
			body->SetGravityScale(1.0);
			return false;
		}
	}else{
		if (laddersTouching >0){
			return true;
		}else{
			body->SetGravityScale(1.0);
			return false;
		}
	}
}

/*informs of passage of time*/
void Megaman::tick(float time) {
	Character::tick(time);
	inmuneTime.dec(time);
}

void Megaman::informClientLifeChange() {
	Game* game = clientData->getGame();
	std::stringstream msj;
	int percentage =
			(int) ((((float) life.getCurrent())) / life.getMax() * 100);
	msj << LIFE_STATUS << " " << clientData->getClientNumber() << " "
			<< percentage;
	game->notify(new MessageSent(msj.str(), clientData->getDescriptor()));
}

/* increases enegry by amount*/
void Megaman::heal(uint amount) {
	this->life.inc(amount);
	LOG(INFO)<<objectId<<" healed, life left: "<<life.getCurrent();
	informClientLifeChange();
}

/* increases charge by amount*/
void Megaman::charge(uint amount) {
	//todo charge weapon/s
	LOG(INFO)<<objectId<<" charged by: "<<amount;
}

/* damages him*/
void Megaman::damage(Bullet* bullet) {
	if(inmuneTime.getCurrent()==0){
		Character::damage(bullet);
		inmuneTime.maxOut();
	}
	informClientLifeChange();
}

/*changes the spwan point*/
void Megaman::setSpawnPos(b2Vec2& newPos) {
	spawnPoint.x=newPos.x;
	spawnPoint.y=newPos.y;
}

/*registers him in level as a megaman*/
void Megaman::registerIn(MyLevel* level) {
	level->addMegaman(this);
}

bool Megaman::isJumping() {
	return Character::isJumping() && !checkClimbing();
}

/* returns sprite id according to jump state, climbing
 * or just walking/idle*/
int Megaman::getSpriteId() {
	if(this->isJumping())
		return jumpingSpriteId;
	else if(checkClimbing())
		return climbingSpriteId;
	else
		return spriteId;
}

void Megaman::assignOwner(ClientData* clientData) {
	this->clientData=clientData;
	informClientLifeChange();
}

/*adds a life*/
void Megaman::addLife() {
	if(clientData && !dead)
		clientData->getLives().inc(1);
}

/*redraws as a character, then send life satatus*/
void Megaman::redrawForClients(Game* game, MyLevel* level, bool checkChanges) {
	Character::redrawForClients(game,level,checkChanges);
}
