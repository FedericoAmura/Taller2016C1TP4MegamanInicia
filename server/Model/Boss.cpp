//
// Created by marcos on 16/06/16.
//

#include <iostream>
#include "Boss.h"
#include "../../common/CommunicationCodes.h"
#include "../Event.h"
#include "../Game.h"

#define IDLE_DISTANCE 10
#define ATTACKING_DISTANCE IDLE_DISTANCE
#define PUNCH_DISTANCE 0.1

Boss::Boss(b2World* w, Json::Value& json, const b2Vec2& pos, MyLevel* lvl)
        : Enemy(w, json, pos, lvl),
          lifeChanged(true){
    setState("#jumping");
    hSpeed = json["HSpeed"].asFloat();
    walking_time = json["walking time"].asFloat();
    jumping_time = json["jumping time"].asFloat();
    attacking_time = json["attacking time"].asFloat();
    punching_dmg = json["punching damage"].asInt();
}

/*when boss dies the game is won*/
void Boss::kill() {
	level->win();
}

void Boss::redrawForClients(Game* game, MyLevel* level, bool checkChanges) {
	Character::redrawForClients(game, level, checkChanges);
	if(!dead && lifeChanged){
		lifeChanged = false;
		std::stringstream msj;
		int percentage =
				(int) ((((float) (life.getCurrent())) / life.getMax() * 100));
		msj << LIFE_STATUS << " 0 "	<< percentage;
		game->notify(new MessageSent(msj.str(), 0));
	}
}

void Boss::damage(Bullet* bullet){
	lifeChanged=true;
	Character::damage(bullet);
}

void Boss::tick(float time) {
    b2Vec2 aim = setAim();
    Character::tick(time);
    if (state == "#jumping"){
        executeJump(time, jumping_time);
        shoot();
    } else if (state == "#walking") {
        executeWalk(walking_time, aim);
    } else if (state == "#attacking") {
        executeAttack(attacking_time);
    }
}

void Boss::jump() {
    b2Vec2 vel = body->GetLinearVelocity();
    b2Vec2 aim = setAim();
    if (float (aim.x) * hSpeed < 0) hSpeed = -hSpeed;
    vel.x = hSpeed;
    vel.y = jSpeed;
    body->SetLinearVelocity(vel);
}

void Boss::executeJump(float time, float jump_time) {
    elapse(jump_time, "#walking");
    jumpTime.dec(time);
    if (jumpTime.getCurrent() == 0){
        jump();
        shoot();
        jumpTime.maxOut();
    }
    shoot();
}

void Boss::executeWalk(float walk_time, b2Vec2& aim) {
    elapse(walk_time, "#attacking");
    b2Vec2 vel = body->GetLinearVelocity();
    if (float (aim.x) * hSpeed < 0) hSpeed = -hSpeed;
    vel.x = hSpeed;
    body->SetLinearVelocity(vel);
    if (fabs(aim.x) < PUNCH_DISTANCE) {
        Megaman* m = level->getNearestMegaman(this->getPos());
        m->damage(punching_dmg);
    };
}

void Boss::executeAttack(float attack_time) {
    elapse(attack_time, "#jumping");
    shoot();
}

void Boss::elapse(float transition_time, std::string next_state) {
    timer_elapsed = clock();
    if (float(timer_elapsed - timer_begin)/CLOCKS_PER_SEC > transition_time){
        setState(next_state);
    }
}












