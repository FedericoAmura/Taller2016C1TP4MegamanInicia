//
// Created by marcos on 16/06/16.
//

#include "Boss.h"
#include "../../common/CommunicationCodes.h"
#include "../Event.h"
#include "../Game.h"

#define IDLE_DISTANCE 10
#define ATTACKING_DISTANCE IDLE_DISTANCE

Boss::Boss(b2World* w, Json::Value& json, const b2Vec2& pos, MyLevel* lvl)
        : Enemy(w, json, pos, lvl),
          lifeChanged(true){
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

void Boss::executeJump(float time) {
    jumpTime.dec(time);
    if (jumpTime.getCurrent() == 0){
        jump();
        jumpTime.maxOut();
    }
}

void Boss::tick(float time) {
    setAim();
    Character::tick(time);
    executeJump(time);
    shoot();
}

void Boss::jump() {
    b2Vec2 vel = body->GetLinearVelocity();
    b2Vec2 aim = setAim();
    if (float (aim.x) * hSpeed < 0) hSpeed = -hSpeed;
    vel.x = hSpeed;
    vel.y = jSpeed;
    body->SetLinearVelocity(vel);
}






