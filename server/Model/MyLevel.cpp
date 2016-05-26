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
	//creo piso
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, -1);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	b2PolygonShape polygonShape;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;

	polygonShape.SetAsBox( w_width/2, 1, b2Vec2(w_width/2, 0), 0);//ground
	groundBody->CreateFixture(&myFixtureDef);
	polygonShape.SetAsBox( w_width/2, 1, b2Vec2(w_width/2, w_height), 0);//ceiling
	groundBody->CreateFixture(&myFixtureDef);
	polygonShape.SetAsBox( 1, w_height/2, b2Vec2(0-1, w_height/2), 0);//left wall
	groundBody->CreateFixture(&myFixtureDef);
	polygonShape.SetAsBox( 1, w_height/2, b2Vec2(w_width+1, w_height/2), 0);//right wall
	groundBody->CreateFixture(&myFixtureDef);

	//creo megaman, por ahora caja
	megaman= new LevelObject(&world,level_json["megaman"],b2Vec2(50,50));
}

MyLevel::~MyLevel() {
	delete megaman;
}

/*informs whether the thread is(should be) running*/
bool MyLevel::isRunning(){
	Lock l(runningMutex);
	return running;
}

std::string numeroATexto(float numero) {
	std::stringstream ss;
	ss << std::fixed << std::setprecision(3)<< numero;
	return ss.str();
}

/*transforms box2d position to client position format*/
std::string MyLevel::posToString(b2Vec2 pos){
	float p1x = 5;
	float p1y = 5;
	float p2x = pos.x *scale;
	float p2y = (w_height-pos.y) *scale;
	std::string pos1 = "X1:" + numeroATexto(p1x) + "-Y1:" + numeroATexto(p1y);
	std::string pos2 = "X2:" + numeroATexto(p2x) + "-Y2:" + numeroATexto(p2y);
	std::string final= pos1+"/"+pos2;
	return final;
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
		//todo informar de todos los cambios
		std::string msj=posToString(getPosMegaman());
		game->notify(new MessageSent(msj,0));
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

/*returns the vector postition of megaman according to box2d simulation*/
b2Vec2 MyLevel::getPosMegaman(){
	return megaman->getPos();
}
