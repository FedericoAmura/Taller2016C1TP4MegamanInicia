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

#include "../Event.h"
#include "../Game.h"
#include "../json/json.h"
#include "LevelObject.h"

void MyLevel::createBoundaries() {
	//window borders
	b2BodyDef bordersBodyDef;
	bordersBodyDef.position.Set(0, -1);
	b2Body* bordersBody = world.CreateBody(&bordersBodyDef);
	b2PolygonShape borderShape;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &borderShape;
	borderShape.SetAsBox(w_width / 2, 1, b2Vec2(w_width / 2, 0), 0); //ground
	bordersBody->CreateFixture(&myFixtureDef);
	borderShape.SetAsBox(w_width / 2, 1, b2Vec2(w_width / 2, w_height), 0); //ceiling
	bordersBody->CreateFixture(&myFixtureDef);
	borderShape.SetAsBox(1, w_height / 2, b2Vec2(0 - 1, w_height / 2), 0); //left wall
	bordersBody->CreateFixture(&myFixtureDef);
	borderShape.SetAsBox(1, w_height / 2, b2Vec2(w_width + 1, w_height / 2), 0); //right wall
	bordersBody->CreateFixture(&myFixtureDef);
}

MyLevel::MyLevel(Game* j,std::string lvlFileName)
:world(b2Vec2(0,-10),true),running(false),game(j) {
	world.SetContinuousPhysics(true);
	world.SetContactListener(this);
	/*abro archivo json*/
	std::ifstream in(lvlFileName);
	LOG(INFO)<<"abierto archivo: "<<lvlFileName;
	Json::Value level_json;
	in >> level_json;
	LOG(INFO)<<"levantado con Json exitoso";
	/*seteo variables mundo*/
	Json::Value world_json=level_json["world"];
	this->w_height=world_json["height"].asFloat();
	this->w_width=world_json["width"].asFloat();
	this->stepsPerSecond=world_json["steps/second"].asFloat();
	this->scale=world_json["scale"].asFloat();
	LOG(INFO)<<"w_height: "<<w_height;
	LOG(INFO)<<"w_width: "<<w_width;
	LOG(INFO)<<"stepsPerSecond: "<<stepsPerSecond;
	LOG(INFO)<<"scale: "<<scale;
	world.SetGravity(b2Vec2(0,world_json["gravity"].asFloat()));
	LOG(INFO)<<"gravity: "<<world.GetGravity().y;
	//window borders
	createBoundaries();
	//creo megaman, por ahora caja
	Json::Value obj_json=level_json["megaman"];
	b2Vec2 pos(obj_json["posX"].asFloat(), obj_json["posY"].asFloat());
	megaman = new LevelObject(&world, obj_json, pos, 9000);
	std::stringstream msj;
	msj<<"1 "<<megaman->getId()<<megaman->getSpriteId();
	msj<<"0 "<<posToString(megaman->getPos());
	game->notify(new MessageSent(msj.str(),0));
}

MyLevel::~MyLevel() {
	delete megaman;
}

/*informs whether the thread is(should be) running*/
bool MyLevel::isRunning(){
	Lock l(runningMutex);
	return running;
}

/*transforms box2d position to client position format*/
std::string MyLevel::posToString(b2Vec2 pos){
	float px = pos.x *scale;
	float py = (w_height-pos.y) *scale;
	std::stringstream positionString;
	positionString.precision(2);
	positionString<<std::fixed<<px<<" "<<py;
	return positionString.str();
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
		//informar de todos los cambios, mediante move code
		std::stringstream msj;
		msj<<"3 "<<megaman->getId()<<" "<<posToString(megaman->getPos());
		game->notify(new MessageSent(msj.str(),0));

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

