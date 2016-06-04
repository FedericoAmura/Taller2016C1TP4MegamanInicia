/*
 * Spawner.cpp
 *
 *  Created on: Jun 2, 2016
 *      Author: nicolas
 */

#include "Spawner.h"
#include <Box2D/Box2D.h>
#include "MyLevel.h"

/*creates spawner for id enemy at pos. must be activated before use
 * to activate use spawnedFalse*/
Spawner::Spawner(int id, b2Vec2& pos, MyLevel* lvl):
id(id),
pos(pos),
level(lvl),
spawned(false){}

Spawner::~Spawner() {}

/*if it hasnt spawned, it spawns a new enemy*/
void Spawner::spawn() {
	if( (!spawned) && level->posInWindow(pos) ){
		spawned=true;
		level->newObject(new ObjectInfo(id,pos));
	}
}

/*used to make spawner able to spawn again*/
void Spawner::spawnedFalse() {
	spawned=false;
}
