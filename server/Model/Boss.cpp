//
// Created by marcos on 16/06/16.
//

#include "Boss.h"
#include "../../common/CommunicationCodes.h"
#include "../Event.h"
#include "../Game.h"

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
		lifeChanged=false;
		std::stringstream msj;
		int percentage =
				(int) ((((float) (life.getCurrent())) / life.getMax() * 100));
		msj << LIFE_STATUS << " 0 "	<< percentage;
		game->notify(new MessageSent(msj.str(), 0));
	}
}
/*
void Boss::jump() {
    Megaman* nearest = level->getNearestMegaman(this->getPos());
    b2Vec2 difference = nearest->getPos();
    difference -= this->getPos();
    if (difference.x <= 0){
        if (direction != LEFT){
            direction = LEFT;
            spriteChanged = true;
        }
        hSpeed = -hSpeed;
    } else {
        if (direction != RIGHT){
            direction = RIGHT;
            spriteChanged = true;
        }
    }
    if(canJump){
        b2Vec2 vel = body->GetLinearVelocity();
        vel.x = hSpeed;
        vel.y = jSpeed;
        body->SetLinearVelocity(vel);
    }
}

void Boss::tick(float time) {
    Enemy::tick(time);
    jump();
}
*/