/*
 * MyLevel.cpp
 *
 *  Created on: May 21, 2016
 *      Author: nicolas
 */

#include "MyLevel.h"

#include <Box2D/Box2D.h>
#include <string>
#include <sstream>
#include <glog/logging.h>
#include <unistd.h>//usleep
#include <iomanip>//setprecision
#include <iostream>//fixed
#include <fstream>//ifstream
#include <map>

#include "../Event.h"
#include "../Game.h"
#include "../json/json.h"
#include "LevelObject.h"
#include "Megaman.h"
#include "Obstacle.h"

#define W_WIDTH 100
#define W_HEIGHT 100

MyLevel::MyLevel(Game* j,std::string lvlFileName)
:world(b2Vec2(0,-10),true),running(false),game(j) {
	world.SetContinuousPhysics(true);
	world.SetContactListener(this);
	/*abro configuraciones*/
	Json::Value config_json;
	fileToJson("../server/Model/config.json",config_json);
	/*cargo nivel*/
	Json::Value level_json;
	fileToJson(lvlFileName,level_json);
	/*seteo variables mundo*/
	Json::Value world_json=config_json["world"];
	this->w_height=level_json["width"].asInt();
	this->w_width=level_json["length"].asInt();
	this->stepsPerSecond=world_json["steps/second"].asFloat();
	world.SetGravity(b2Vec2(0,world_json["gravity"].asFloat()));

	this->hScale=W_HEIGHT/w_height;
	this->vScale=W_WIDTH/w_width;

	LOG(INFO)<<"w_height: "<<w_height;
	LOG(INFO)<<"w_width: "<<w_width;
	LOG(INFO)<<"stepsPerSecond: "<<stepsPerSecond;
	LOG(INFO)<<"gravity: "<<world.GetGravity().y;
	//window borders
	createBoundaries();
	//load all objects of the level
	Json::Value objetosNivel=level_json["foreground"];
	Json::ValueIterator it=objetosNivel.begin();
	for(; it!=objetosNivel.end(); it++){
		LevelObject* newObj=createObject(*it,config_json);
		if(newObj!= nullptr)
			objects[newObj->getId()]=newObj;
	}
}

/*opens file and sends data to json*/
void MyLevel::fileToJson(std::string fileName, Json::Value& json){
	std::ifstream configFile(fileName);
	LOG(INFO)<<"abierto archivo: "<<fileName;
	configFile >> json;
}

MyLevel::~MyLevel() {
	std::map<int,LevelObject*>::iterator it=objects.begin();
	for(;it!=objects.end();it++){
		delete it->second;
	}
}

/*retruns new object if id has config, nullptr if not*/
LevelObject* MyLevel::createObject(Json::Value objectJson,Json::Value config) {
	int id=objectJson["id"].asInt();
	bool creado=false;
	LevelObject* objetoNuevo;
	//todo cambiar switch por algo automatico, implica cambios en config.json
	switch(id){
	case 9000:{
		//create megaman
		if (megaman==nullptr){
			creado=true;
			b2Vec2 pos=jsonPosToWorldPos(objectJson["x"].asInt(),
					objectJson["y"].asInt());
			megaman = new Megaman(&world, config["megaman"], pos);
			objetoNuevo=megaman;
		}
		break;
	}
	case 4119:{
		//create wall
		creado=true;
		b2Vec2 pos=jsonPosToWorldPos(objectJson["x"].asInt(),
				objectJson["y"].asInt());
		objetoNuevo = new Obstacle(&world,config["wall"],pos,4119);
		break;
	}
	default:
		break;
	}
	if(creado){
		/*notify clients about creation*/
		std::stringstream msj;
		msj<<"1 "<<objetoNuevo->getId()<<" "<<objetoNuevo->getSpriteId();
		msj<<" 0 "<<posToString(objetoNuevo->getPos());
		game->notify(new MessageSent(msj.str(),0));
		return objetoNuevo;
	}else{
		return nullptr;
	}
}

void MyLevel::createBoundaries() {
	//window borders
	float thickness=0.01;
	b2BodyDef bordersBodyDef;
	bordersBodyDef.position.Set(0, -thickness);
	b2Body* bordersBody = world.CreateBody(&bordersBodyDef);
	b2PolygonShape borderShape;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &borderShape;
	borderShape.SetAsBox(w_width / 2, thickness,
			b2Vec2(w_width / 2, 0), 0); //ground
	bordersBody->CreateFixture(&myFixtureDef);
	borderShape.SetAsBox(w_width / 2, thickness,
			b2Vec2(w_width / 2, w_height), 0); //ceiling
	bordersBody->CreateFixture(&myFixtureDef);
	borderShape.SetAsBox(thickness, w_height / 2,
			b2Vec2(0 - 1, w_height / 2), 0); //left wall
	bordersBody->CreateFixture(&myFixtureDef);
	borderShape.SetAsBox(thickness, w_height / 2,
			b2Vec2(w_width + 1, w_height / 2), 0); //right wall
	bordersBody->CreateFixture(&myFixtureDef);
}

/*informs whether the thread is(should be) running*/
bool MyLevel::isRunning(){
	Lock l(runningMutex);
	return running;
}

/*transforms box2d position to client position format*/
std::string MyLevel::posToString(b2Vec2 pos){
	//devuelvo esq iz sup
	float px = pos.x-0.5;
	float py = (W_HEIGHT-pos.y+0.5);
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
	posY=w_height-posY;//corrijo por diferente centro de coordenadas
	b2Vec2 pos(posX,posY);
	return pos;
}

/*runs the physics simulation until it is stopped*/
void MyLevel::run(){
	{
		Lock l(runningMutex);
		running=true;
	}
	float32 timeStep = 1.0f / stepsPerSecond;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	LOG(INFO)<<"physics simulation of level started";

	while(isRunning()){
		world.Step(timeStep, velocityIterations, positionIterations);
		//todo si jugadores pasan mitad pantalla mover

		//todo loop sobre objetos
		//informar de todos los cambios, mediante move code
		std::map<int,LevelObject*>::iterator it=objects.begin();
		for(;it!=objects.end();it++){
			LevelObject* obj= it->second;
			if(obj->changed()){
				std::stringstream msj;
				msj<<"3 "<<obj->getId()<<" "<<posToString(obj->getPos());
				game->notify(new MessageSent(msj.str(),0));
			}
		}


		usleep(timeStep* 1000000 );
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
	megaman->move(boton);
}
