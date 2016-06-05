/*
 * ObjectFactory.cpp
 *
 *  Created on: Jun 3, 2016
 *      Author: nicolas
 */

#include "ObjectFactory.h"

#include <Box2D/Dynamics/b2Body.h>
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
		}else{
			newObject = new Enemy(world, config[idAsString], pos,level);
		}
		break;
	}
	case 2:{
		created=true;
		newObject= new Bullet(world,config[idAsString],pos,id);
		break;
	}
	case 3:{
		created=true;
		if(id==BIG_ENERGY || id==SMALL_ENERGY)
			newObject= new EnergyItem(world,config[idAsString],pos,id,level);
		if(id==BIG_PLASMA || id==SMALL_PLASMA)
			newObject= new PlasmaItem(world,config[idAsString],pos,id,level);
		if(id==LIFE)
			newObject= new LifeItem(world,config[idAsString],pos,id,level);
		break;
	}
	case 4:{
		//create obstacle
		created=true;
		newObject = new Obstacle(world,config["wall"],pos,id);
		break;
	}
	case 5:{
		// create special obstacle
		created=true;
		if(id==SPIKE){
			newObject = new Spikes(world,config["spikes"],pos,id);
		}else{
			//escalera
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
	if(created){
		return newObject;
	}else{
		return nullptr;
	}
}
