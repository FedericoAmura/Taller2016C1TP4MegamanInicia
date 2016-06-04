/*
 * MyLevel.cpp
 *
 *  Created on: May 21, 2016
 *      Author: nicolas
 */

#include "MyLevel.h"

#include <Box2D/Box2D.h>
#include <string>
#include <sstream>		//stringstream
#include <glog/logging.h>
#include <unistd.h>		//usleep
#include <iomanip>		//setprecision
#include <iostream>		//fixed
#include <fstream>		//ifstream
#include <map>
#include <exception>	//catch
#include <vector>
#include <algorithm>    // std::find

#include "../Event.h"
#include "../Game.h"
#include "../json/json.h"
#include "LevelObject.h"
#include "MyContactListener.h"
#include "../common/CommunicationCodes.h"
#include "Megaman.h"
#include "ObjectFactory.h"
#include "ObjectInfo.h"
#include "Bullet.h"

#define COFIG_FILE "../server/Model/config.json"
#define IGNORE 0

MyLevel::MyLevel(Game* j,std::string lvlFileName):
world(b2Vec2(0,-10)),
running(false),
game(j),
factory(&world,this){
	LevelObject::resetIds();
	megaman=nullptr;
	world.SetContinuousPhysics(true);
	world.SetContactListener(&contactListener);
	windowPos.x=0;
	windowPos.y=0;
	/*abro configuraciones*/
	Json::Value config_json;
	fileToJson(COFIG_FILE,config_json);
	/*cargo nivel*/
	Json::Value level_json;
	fileToJson(lvlFileName,level_json);
	/*seteo variables mundo*/
	this->worldHeight=level_json["width"].asInt();
	this->worldWidth=level_json["length"].asInt();

	Json::Value world_json=config_json["world"];
	this->stepsPerSecond=world_json["steps/second"].asFloat();
	world.SetGravity(b2Vec2(0,world_json["gravity"].asFloat()));
	this->windowHeight=world_json["windowHeight"].asFloat();
	this->windowWidth=world_json["windowWidth"].asFloat();
	//window borders
	createBoundaries();
	//load all objects of the level
	Json::Value objetosNivel=level_json["foreground"];
	Json::ValueIterator it=objetosNivel.begin();
	for(; it!=objetosNivel.end(); it++){
		int id=(*it)["id"].asInt();
		b2Vec2 pos=jsonPosToWorldPos((*it)["x"].asInt(),
				(*it)["y"].asInt());
		if(id/1000 ==1){
			addSpawner(id,pos);
		}else{
			createObject(id,pos);
		}
	}
	spawn();
}

/*opens file and sends data to json*/
void MyLevel::fileToJson(std::string fileName, Json::Value& json){
	std::ifstream configFile(fileName);
	//LOG(INFO)<<"abierto archivo: "<<fileName;
	configFile >> json;
}

MyLevel::~MyLevel() {
	std::map<int,LevelObject*>::iterator objectIt=objects.begin();
	for(;objectIt!=objects.end();objectIt++){
		delete objectIt->second;
	}
	std::vector<Spawner*>::iterator spawnerIt=spawners.begin();
	for(;spawnerIt!=spawners.end();spawnerIt++){
		delete (*spawnerIt);
	}
}

/*retruns new object if id has config, nullptr if not*/
LevelObject* MyLevel::createObject(int id,b2Vec2& pos) {
	LevelObject* newObject=factory.createObject(id,pos);
	if(newObject){
		int objectType=(int)newObject->getSpriteId()/1000;
		if(objectType==9 && megaman==nullptr){//megaman
			megaman=(Megaman*) newObject;
		}
		if(objectType==1 || objectType==9){//character
			characters[newObject->getId()]=(Character*)newObject;
		}
		/*notify clients about creation*/
		int spriteId=newObject->getSpriteId();
		if(!(spriteId==IGNORE)){
			std::stringstream msj;
			msj<<DRAW<<" "<<newObject->getId()<<" "<<spriteId;
			msj<<" 0 "<<posToString(newObject->getPos());
			game->notify(new MessageSent(msj.str(),0));
		}
		objects[newObject->getId()]=newObject;
		return newObject;
	}else{
		return nullptr;
	}
}

void MyLevel::createBoundaries() {
	b2Vec2 pos(windowPos.x,windowPos.y);
	pos.x+=windowWidth/2;
	pos.y+=windowHeight/2;
	createObject(0,pos);
}

/*informs whether the thread is(should be) running*/
bool MyLevel::isRunning(){
	Lock l(runningMutex);
	return running;
}

/*transforms box2d position to client position format*/
std::string MyLevel::posToString(b2Vec2 pos){
	float px = pos.x;
	float py = windowHeight-pos.y;
	//todo check reference frame

	std::stringstream positionString;
	positionString.precision(2);
	positionString<<std::fixed<<px<<" "<<py;
	return positionString.str();
}

/*devuelve la pos correspondiente al centro del tile pasado*/
b2Vec2 MyLevel::jsonPosToWorldPos(int x, int y) {
	float posX,posY;
	posX=x+0.5;//desfaso centro medio tile
	posY= y+0.5;//desfaso centro medio tile
	posY=worldHeight-posY;//corrijo por diferente centro de coordenadas
	b2Vec2 pos(posX,posY);
	return pos;
}

/*informs the client of the new position of the level objects that changed*/
void MyLevel::redrawForClient(){
	std::map<int,LevelObject*>::iterator it=objects.begin();
	for(;it!=objects.end();it++){
		LevelObject* obj= it->second;
		if(obj->changed()){
			std::stringstream msj;
			b2Vec2 corner;
			obj->copyCorner(corner);
			msj<<MOVE<<" "<<obj->getId()<<" "<<posToString(corner);
			game->notify(new MessageSent(msj.str(),0));
		}
	}
}

void MyLevel::removeDead(){
	while(!toRemove.empty()){
		LevelObject* dead= toRemove.front();
		toRemove.pop();
		//notify clients
		std::stringstream killMsg;
		int deadId=dead->getId();
		killMsg<<KILL<<" "<<deadId;
		game->notify(new MessageSent(killMsg.str(),0));
		//erase from object tracker
		objects.erase(deadId);
		//erase from characters tracker
		characters.erase(deadId);
		//if no megamans left exit
		if(dead==megaman){
			game->notify(new LevelFinished(-1));
			this->stop();
		}
		//delete the dead
		delete dead;
	}
}

/*runs the physics simulation until it is stopped*/
void MyLevel::run(){
	{
		Lock l(runningMutex);
		running=true;
	}
	float32 timeStep = 1.0f / stepsPerSecond;//seconds
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	LOG(INFO)<<"physics simulation of level started";

	try{
		while(isRunning()){
			createNewObjects();
			//todo si jugadores pasan mitad pantalla mover
			world.Step(timeStep, velocityIterations, positionIterations);
			tickAll(timeStep);
			removeDead();
			respawnAll();
			redrawForClient();
			usleep(timeStep* 1000000 );
		}
	}catch(std::exception& e){
		LOG(ERROR)<<e.what();
	}
	LOG(INFO)<<"physics simulation of level stopped";
}

/*stops physics simulation after current frames is proccessed*/
void MyLevel::stop(){
	Lock l(runningMutex);
	running=false;
}

/*makes the megaman move according to the input*/
void MyLevel::moveMegaman(char boton){
	if(megaman!=nullptr)
		megaman->move(boton);
}

/*adds object to remove list*/
void MyLevel::remove(LevelObject* deadObject){
	toRemove.push(deadObject);
}

/*respawns objects in respawn list*/
void MyLevel::respawnAll() {
	while(!toRespawn.empty()){
		toRespawn.front()->spawn();
		toRespawn.pop();
	}
}

/*adds megaman to respawn list*/
void MyLevel::respawn(Megaman* meg) {
	toRespawn.push(meg);
}

/*informs all characters of the passage of a time step*/
void MyLevel::tickAll(float time) {
	std::map<int,Character*>::iterator it=characters.begin();
	for(; it!=characters.end(); it++){
		it->second->tick(time);
	}
}

void MyLevel::createNewObjects() {
	while(!toCreate.empty()){
		ObjectInfo* info=toCreate.front();
		toCreate.pop();

		b2Vec2 pos=info->getPos();
		LevelObject* obj=createObject(info->getId(),pos);
		if(obj){
			int objectType=obj->getSpriteId()/1000;
			if(objectType==2){//bullet
				Bullet* bullet=(Bullet*)obj;
				BulletInfo* bInfo=(BulletInfo*)info;
				bullet->initialize(bInfo->getGroupBits(),bInfo->getSpeed(),this);
			}
		}
		delete info;
	}
}

/*requests to create a new object at pos*/
void MyLevel::newObject(ObjectInfo* info) {
	toCreate.push(info);
}

void MyLevel::addSpawner(int id, b2Vec2& pos) {
	spawners.push_back(new Spawner(id,pos,this));
}

void MyLevel::spawn() {
	std::vector<Spawner*>::iterator spawnerIt=spawners.begin();
	for(; spawnerIt!=spawners.end(); spawnerIt++){
		(*spawnerIt)->spawn();
	}
}

bool MyLevel::posInWindow(b2Vec2& pos) {
	b2Vec2 relativePos;
	relativePos.x=pos.x-windowPos.x;
	relativePos.y=pos.y-windowPos.y;
	if(relativePos.x<windowWidth && relativePos.y<windowHeight)
		return true;
	else
		return false;
}


