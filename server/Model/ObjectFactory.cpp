/*
 * ObjectFactory.cpp
 *
 *  Created on: Jun 3, 2016
 *      Author: nicolas
 */

#include "ObjectFactory.h"

#include <Box2D/Dynamics/b2Body.h>
#include <sstream>
#include <string>
#include <fstream>
#include <queue>

#include "../../json/json.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Megaman.h"
#include "Obstacle.h"
#include "LevelObject.h"

struct b2Vec2;

#define COFIG_FILE "../server/Model/config.json"

ObjectFactory::ObjectFactory(b2World* w, MyLevel* lvl):
				world(w),
				level(lvl){}

ObjectFactory::~ObjectFactory() {}

LevelObject* ObjectFactory::createObject(int id, b2Vec2& pos) {
	Json::Value config;
	std::ifstream configFile(COFIG_FILE);
	//LOG(INFO)<<"abierto archivo: "<<fileName;
	configFile >> config;
	int objectType=(int)id/1000;
	bool created=false;
	LevelObject* newObject;
	std::stringstream converter;
	converter<<id;
	std::string idAsString=converter.str();
	//todo cambiar hardcodeo por algo mas automatico, implica cambios en config.json
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
		//todo more enemies
		newObject = new Enemy(world, config[idAsString], pos,level);
		break;
	}
	case 2:{
		created=true;
		newObject= new Bullet(world,config[idAsString],pos,id);
		break;
	}
	case 3:
		//todo create item
		break;
	case 4:{
		//create obstacle
		created=true;
		newObject = new Obstacle(world,config["wall"],pos,id);
		break;
	}
	case 5:{
		// create special obstacle
		created=true;
		if(id==5003){
			newObject = new Spikes(world,config["spikes"],pos,id);
		}else{
			//escalera
			newObject= new Ladder(world,config["wall"],pos,id);
		}
		break;
	}
	default:
		break;
	}
	if(created){
		return newObject;
	}else{
		return nullptr;
	}
}
