/*
 * ObjectFactory.cpp
 *
 *  Created on: Jun 3, 2016
 *      Author: nicolas
 */

#include "ObjectFactory.h"

#include <Box2D/Box2D.h>
#include <glog/logging.h>
#include <sstream>
#include <fstream> //ifstream
#include <string>

#include "../../json/json.h"
#include "../../entities.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Items.h"
#include "Megaman.h"
#include "Obstacle.h"
#include "MyLevel.h"

struct b2Vec2;

#define COFIG_FILE "../server/Model/config.json"

ObjectFactory::ObjectFactory(b2World* w, MyLevel* lvl):
								world(w),
								level(lvl){}

ObjectFactory::~ObjectFactory() {}

std::string ObjectFactory::idToStr(int id) {
	std::stringstream converter;
	converter << id;
	return converter.str();
}

LevelObject* ObjectFactory::createObject(ObjectInfo* info) {
	Json::Value config;
	std::ifstream configFile(COFIG_FILE);
	//LOG(INFO)<<"abierto archivo: "<<fileName;
	configFile >> config;
	int id= info->getId();
	b2Vec2 pos;
	pos.x= info->getPos().x;
	pos.y= info->getPos().y;
	int objectType=(int)id/1000;
	bool created=false;
	LevelObject* newObject;
	std::string idAsString=idToStr(id);
	switch(objectType){
	case 9:{
		//create megaman
		created=true;
		newObject = new Megaman(world, config["megaman"], pos,level);
		break;
	}
	case 0:{
		created=true;
		newObject = new Obstacle(world,config["windowBoundaries"],pos,0);
		break;
	}
	case 1:{
		created=true;
		//todo more enemies? or shield is from json
		if(id==BUMBY_0){
			newObject = new FlyingEnemy(world, config[idAsString], pos,level);
		}else if(id==BOSS_BOMBMAN || id==BOSS_SPARKMAN ||
				id==BOSS_MAGNETMAN || id==BOSS_RINGMAN || id==BOSS_FIREMAN){
			newObject = new Boss(world, config[idAsString], pos,level);
		}else{
			newObject = new Enemy(world, config[idAsString], pos,level);
		}
		break;
	}
	case 2:{
		created=true;
		newObject= new Bullet(world,config[idAsString],pos,id);
		if(newObject){
			Bullet* bullet=(Bullet*)newObject;
			BulletInfo* bInfo=(BulletInfo*)info;
			bullet->initialize(bInfo->getGroupBits(),bInfo->getSpeed(),level);
		}
		break;
	}
	case 3:{
		id= Item::chooseDrop();
		idAsString=idToStr(id);
		if(id){
			created=true;
			LOG(INFO)<<"random drop, id: "<<id;
		}
		if((id==BIG_ENERGY || id==SMALL_ENERGY)&& created)
			newObject= new EnergyItem(world,config[idAsString],pos,id,level);
		if((id==BIG_PLASMA || id==SMALL_PLASMA)&& created)
			newObject= new PlasmaItem(world,config[idAsString],pos,id,level);
		if((id==LIFE)&& created)
			newObject= new LifeItem(world,config[idAsString],pos,id,level);
		break;
	}
	case 4:{
		//create obstacle
		if(id==BOSS_DOOR){
			created=true;
			newObject = new BossDoor(world,config["wall"],pos,id,level);
		}else{
			created=true;
			newObject = new Obstacle(world,config["wall"],pos,id);
		}
		break;
	}
	case 5:{
		// create special obstacle
		if(id==SPIKE){
			created=true;
			newObject = new Spikes(world,config["spikes"],pos,id);
		}else{
			created=true;
			newObject= new Ladder(world,config["wall"],pos,id);
		}
		break;
	}
	default:{
		created=false;
		LOG(INFO)<<"id no reconocido, error en creacion objeto";
		break;
	}
	}
	if(created && newObject){
		return newObject;
	}else{
		return nullptr;
	}
}
