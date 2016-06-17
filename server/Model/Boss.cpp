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

Boss::Boss(b2World* w, Json::Value& json, const b2Vec2& pos, MyLevel* lvl)
        : Enemy(w, json, pos, lvl),
          lifeChanged(true){
    setState("#jumping");
    hSpeed = json["HSpeed"].asFloat();
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



void Boss::tick(float time) {
    b2Vec2 aim = setAim();
    Character::tick(time);
    if (state == "#jumping"){
        executeJump(time, 0.05);
        shoot();
    } else if (state == "#walking") {
        std::cout << "walking" << std::endl;
        executeWalk(0.05, aim);
    } else if (state == "#attacking") {
        std::cout << "attacking" << std::endl;
        executeAttack(0.05);
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
    timer_elapsed = clock();
    if (float(timer_elapsed - timer_begin)/CLOCKS_PER_SEC > jump_time){
        setState("#walking");
    }
    jumpTime.dec(time);
    if (jumpTime.getCurrent() == 0){
        jump();
        shoot();
        jumpTime.maxOut();
    }
    shoot();
}

void Boss::executeWalk(float walk_time, b2Vec2& aim) {
    timer_elapsed = clock();
    if (float(timer_elapsed - timer_begin)/CLOCKS_PER_SEC > walk_time){
        setState("#attacking");
    }
    b2Vec2 vel = body->GetLinearVelocity();
    if (float (aim.x) * hSpeed < 0) hSpeed = -hSpeed;
    vel.x = hSpeed;
    body->SetLinearVelocity(vel);
}

void Boss::executeAttack(float attack_time) {
    timer_elapsed = clock();
    shoot();
    if (float(timer_elapsed - timer_begin)/CLOCKS_PER_SEC > attack_time){
        setState("#jumping");
    }
}










