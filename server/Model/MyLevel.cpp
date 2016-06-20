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
#include "Obstacle.h"
#include "Items.h"
#include "../Metadata.h"

#define COFIG_FILE "../server/Model/config.json"
#define IGNORE 0
#define LEFT_ZONE_LIMIT 0.1
#define RIGHT_ZONE_LIMIT 0.9
#define OFFSET 0.1
#define BOSS_CHAMBER_OFFSET 10

MyLevel::MyLevel(Game* j,std::string lvlFileName,Metadata* metadata,int id)
:world(b2Vec2(0,-10)),
 running(false),
 game(j),
 factory(&world,this),
 metadata(metadata),
 id(id),
 bossEncounter(false){
	LevelObject::resetIds();
	boundaries=nullptr;
	world.SetContinuousPhysics(true);
	world.SetContactListener(&contactListener);
	windowPos.x=0;
	windowPos.y=0;
	/*abro configuraciones*/
	Json::Value config_json;
	fileToJson(COFIG_FILE,config_json);

	Item::initializeDropTable(config_json);

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
		ObjectInfo info(id,pos);
		int objectType=id/1000;
		if( objectType==1){
			addSpawner(id,pos);
		}else{
			createObject(&info);
		}
	}
	//load all objects of the level
	Json::Value objetosBossChamber=level_json["chamber"];
	Json::ValueIterator chamberIt=objetosBossChamber.begin();
	for(; chamberIt!=objetosBossChamber.end(); chamberIt++){
		int id=(*chamberIt)["id"].asInt();
		b2Vec2 pos=jsonPosToWorldPos(
				(*chamberIt)["x"].asInt()+worldWidth+BOSS_CHAMBER_OFFSET,
				(*chamberIt)["y"].asInt());
		ObjectInfo info(id,pos);
		int objectType=id/1000;
		if( objectType==1){
			addSpawner(id,pos);
		}else{
			createObject(&info);
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

/*deletes level and frees its members*/
MyLevel::~MyLevel() {
	/*characters and megamans are cleaned with the level objects*/
	std::map<int,LevelObject*>::iterator objectIt=objects.begin();
	for(;objectIt!=objects.end();objectIt++){
		delete objectIt->second;
	}
	std::vector<Spawner*>::iterator spawnerIt=spawners.begin();
	for(;spawnerIt!=spawners.end();spawnerIt++){
		delete (*spawnerIt);
	}
	while(!toCreate.empty()){
		delete toCreate.front();
		toCreate.pop();
	}
}

/*retruns new object if id has config, nullptr if not*/
LevelObject* MyLevel::createObject(ObjectInfo* info) {
	LevelObject* newObject=factory.createObject(info);
	if(newObject!=nullptr){
		int objectType=(int)newObject->getSpriteId()/1000;
		if(objectType==0 && boundaries==nullptr){
			boundaries= newObject;
		}
		newObject->registerIn(this);
		return newObject;
	}else{
		return nullptr;
	}
}

void MyLevel::createBoundaries() {
	if(boundaries){
		remove(boundaries);
	}
	newObject(new ObjectInfo(0,windowPos));
}

/*informs whether the thread is(should be) running*/
bool MyLevel::isRunning(){
	Lock l(runningMutex);
	return running;
}

/*transforms box2d position to client position format*/
std::string MyLevel::posToString(b2Vec2 pos){
	float px = (pos.x-windowPos.x)-0.5;
	float py = windowHeight-(pos.y-windowPos.y)+0.4;

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

/*informs the client of the new position of the level objects in window
 * that changed. If checkChanges is passed as false(note: default is true),
 * then all objects in window are drawn independent of changes*/
void MyLevel::redrawForClient(bool checkChanges){
	std::map<int,LevelObject*>::iterator it=objects.begin();
	for(;it!=objects.end();it++){
		LevelObject* obj= it->second;
		obj->redrawForClients(game,this,checkChanges);
	}
}

void MyLevel::removeDead(){
	while(!toRemove.empty()){
		LevelObject* dead= toRemove.front();
		toRemove.pop();
		int deadId=dead->getId();
		if(dead!=boundaries){
			//notify clients
			std::stringstream killMsg;
			killMsg<<KILL<<" "<<deadId;
			game->notify(new MessageSent(killMsg.str(),0));
		}else{
			boundaries=nullptr;//reset boundaries if removed
		}
		//erase from object tracker
		if(objects.find(deadId)!=objects.end())
			objects.erase(deadId);
		//erase from characters tracker
		if(characters.find(deadId)!=characters.end())
			characters.erase(deadId);
		//erase from megamans tracker
		std::map<int,Megaman*>::iterator megIt=megamans.begin(),
				deleteIt;
		bool found=false;
		for(; megIt!=megamans.end() && !found; megIt++){
			if(megIt->second->getId()==deadId){
				found=true;
				deleteIt=megIt;
			}
		}
		if(found) megamans.erase(deleteIt);
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
	bool bossEncounterStarted=false;
	try{
		while(isRunning()){
			if(!bossEncounterStarted && bossEncounter){
				bossEncounterStarted=true;
				startBossEncounter();
			}
			moveScreen();
			removeDead();
			createNewObjects();
			world.Step(timeStep, velocityIterations, positionIterations);
			tickAll(timeStep);
			redrawForClient();
			respawnAll();
			//if no megamans left exit
			if(allMegamansDead()){
				LOG(INFO)<<"all megamans dead";
				game->notify(new LevelFinished(LOST,id));
				this->stop();
			}
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
void MyLevel::changeKeyState(uint keyState, int client){
	std::map<int,Megaman*>::iterator pos=megamans.find(client);
	if(pos!=megamans.end()){
		Megaman* megaman=pos->second;
		if(!megaman->isDead())
			megaman->changeKeyState(keyState);
	}
}

/*adds object to remove list*/
void MyLevel::remove(LevelObject* deadObject){
	toRemove.push(deadObject);
}

/*returns true if all megamans died*/
bool MyLevel::allMegamansDead() {
	bool allDead = true;
	std::map<int, Megaman*>::iterator megIt = megamans.begin();
	for (; megIt != megamans.end(); megIt++) {
		Megaman* megaman = megIt->second;
		if (!megaman->isDead())
			allDead = false;
	}
	return allDead;
}

/*respawns objects in respawn list*/
void MyLevel::respawnAll() {
	if(allMegamansDead()){
		while(!toRespawn.empty()){
			toRespawn.front()->spawn();
			toRespawn.pop();
		}
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
		createObject(info);
		delete info;
	}
}

/*requests to create a new object at pos*/
void MyLevel::newObject(ObjectInfo* info) {
	toCreate.push(info);
}

/*adds new spawner to level*/
void MyLevel::addSpawner(int id, b2Vec2& pos) {
	spawners.push_back(new Spawner(id,pos,this));
}

/*asks all spawners to determine if they can, and to do, spawn*/
void MyLevel::spawn() {
	std::vector<Spawner*>::iterator spawnerIt=spawners.begin();
	for(; spawnerIt!=spawners.end(); spawnerIt++){
		(*spawnerIt)->spawnedFalse();
		(*spawnerIt)->spawn();
	}
}

/*returns true if pos is inside of current window*/
bool MyLevel::posInWindow(const b2Vec2& pos) {
	b2Vec2 relativePos;
	relativePos.x=pos.x-windowPos.x;
	relativePos.y=pos.y-windowPos.y;
	bool xAxisOk=relativePos.x<=windowWidth && relativePos.x>=0;
	bool yAxisOk=relativePos.y<=windowHeight && relativePos.y>=0;
	if(xAxisOk && yAxisOk)
		return true;
	else
		return false;
}

/*if all megamans are past LEFT or RIGHT zone limit, moves the window.
 * If screen moved spawns new enemies, kills characters outside window,
 * informs client to move all objects*/
void MyLevel::moveScreen() {
	bool inRightZone, inLeftZone;
	inLeftZone= (windowPos.x != 0);//check not left border
	inLeftZone= (!bossEncounter) && inLeftZone;
	std::map<int,Megaman*>::iterator megIt=megamans.begin();
	for(; megIt!=megamans.end(); megIt++){
		Megaman* megaman=megIt->second;
		inLeftZone= inLeftZone && ( megaman->isDead() || megaman->getPos().x <
				(windowPos.x + windowWidth* LEFT_ZONE_LIMIT) );
	}
	if (inLeftZone){
		windowPos.x-=windowWidth*(RIGHT_ZONE_LIMIT-OFFSET);
		if(windowPos.x<0)
			windowPos.x=0;
	}else{
		inRightZone= (windowPos.x+windowWidth)<worldWidth;//check not rigth border
		inRightZone= (!bossEncounter)&& inRightZone;
		megIt=megamans.begin();
		for(; megIt!=megamans.end(); megIt++){
			Megaman* megaman=megIt->second;
			inRightZone= inRightZone && ( megaman->isDead() ||
					megaman->getPos().x >(windowPos.x + windowWidth* RIGHT_ZONE_LIMIT) );
		}
		if (inRightZone){
			windowPos.x+=windowWidth*(RIGHT_ZONE_LIMIT-LEFT_ZONE_LIMIT-OFFSET);
			if((windowPos.x+windowWidth)>worldWidth)
				windowPos.x=worldWidth-windowWidth;
		}
	}
	if(inLeftZone || inRightZone){
		LOG(INFO)<<"screen moved. new position: "<< std::fixed<<
				std::setprecision(2)<<windowPos.x<<" "<<windowPos.y;

		createBoundaries();
		spawn();//create new characters and restores spawners outside

		redrawForClient(false);
	}
}

void MyLevel::startBossEncounter() {
	windowPos.x= worldWidth+BOSS_CHAMBER_OFFSET;
	createBoundaries();
	std::map<int,Megaman*>::iterator megIt=megamans.begin();
	for(; megIt!=megamans.end(); megIt++){
		b2Vec2 newSpawn(windowPos.x+2,windowPos.y+5);
		Megaman* megaman=megIt->second;
		megaman->setSpawnPos(newSpawn);
		megaman->spawn();
	}
	spawn();//create new characters and restores spawners outside
	std::map<int,Character*>::iterator characterIt=characters.begin();
	for(; characterIt!=characters.end(); characterIt++){
		Character* character=characterIt->second;
		if( !posInWindow(character->getPos()) ){
			character->kill();
		}
	}
	redrawForClient(false);
}

void MyLevel::megamanAtDoor(BossDoor* door) {
	uint megamansAlive=0;
	std::map<int,Megaman*>::iterator megIt=megamans.begin();
	for(; megIt!=megamans.end(); megIt++){
		Megaman* megaman=megIt->second;
		if(!megaman->isDead())
			megamansAlive++;
	}
	if(door->getMegamansTouching()==megamansAlive && megamansAlive>0)
		bossEncounter=true;
}

/* adds megaman to megaman tracker if theres space, deletes him if not
 * then adds him as character*/
void MyLevel::addMegaman(Megaman* newMegaman) {
	if(megamans.size()<(uint)metadata->getNumberOfClients()){
		ClientData* clientData=metadata->getClient(megamans.size()+1);
		if(clientData){
			megamans[clientData->getClientNumber()]=newMegaman;
			addCharacter(newMegaman);
			newMegaman->assignOwner(clientData);
		}
	}else{
		delete newMegaman;
	}
}

/*adds character to characters tracker, then adds it as object */
void MyLevel::addCharacter(Character* newCharacter) {
	characters[newCharacter->getId()]=newCharacter;
	addObject(newCharacter);
}

/*adds object to object tracker, then informs clients of new object*/
void MyLevel::addObject(LevelObject* newObject) {
	objects[newObject->getId()]=newObject;
	/*notify clients about creation*/
	int spriteId=newObject->getSpriteId();
	if(spriteId!=IGNORE){
		std::stringstream msj;
		msj<<DRAW<<" "<<newObject->getId()<<" "<<spriteId;
		msj<<" 0 "<<posToString(newObject->getPos());
		game->notify(new MessageSent(msj.str(),0));
	}
}

void MyLevel::win() {
	game->notify(new LevelFinished(WON,id));
}

/*get the nearest megaman or nullptr if they are too far away*/
Megaman* MyLevel::getNearestMegaman(const b2Vec2& pos) {
	Megaman* nearest=nullptr;
	b2Vec2 distance(pos.x,1000);
	b2Vec2 temp;
	std::map<int,Megaman*>::iterator megIt=megamans.begin();
	for(; megIt!=megamans.end(); megIt++){
		temp.x=(*megIt).second->getPos().x;
		temp.y=(*megIt).second->getPos().y;
		temp-=pos;
		if(temp.LengthSquared()<=distance.LengthSquared()
				&& !(*megIt).second->isDead()){
			distance.x=(*megIt).second->getPos().x;
			distance.y=(*megIt).second->getPos().y;
			nearest=(*megIt).second;
		}
	}
	return nearest;
}

void MyLevel::removeClient(int clientNumber) {
	std::map<int,Megaman*>::iterator pos=megamans.find(clientNumber);
	if(pos!=megamans.end()){
		pos->second->clientDisconnected();
	}
}
