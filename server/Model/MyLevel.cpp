/*
 * MyLevel.cpp
 *
 *  Created on: May 21, 2016
 *      Author: nicolas
 */

#include "MyLevel.h"

#include <Box2D/Box2D.h>
#include "../Juego.h"
#include "../Evento.h"
#include <string>
#include <sstream>
#include <glog/logging.h>
#include <unistd.h>

#define STEPS_PER_SECOND 30.0
#define SCALE 1

#define ANCHO_SIM 100
#define ALTO_SIM 100

MyLevel::MyLevel(Juego* j):world(b2Vec2(-0.0f,-100),true),running(false),game(j) {
	world.SetContinuousPhysics(true);
	world.SetContactListener(this);

	//creo piso
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, -1);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	b2PolygonShape polygonShape;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;

	polygonShape.SetAsBox( ANCHO_SIM/2, 1, b2Vec2(ANCHO_SIM/2, 0), 0);//ground
	groundBody->CreateFixture(&myFixtureDef);
	polygonShape.SetAsBox( ANCHO_SIM/2, 1, b2Vec2(ANCHO_SIM/2, ALTO_SIM), 0);//ceiling
	groundBody->CreateFixture(&myFixtureDef);
	polygonShape.SetAsBox( 1, ALTO_SIM/2, b2Vec2(0-1, ALTO_SIM/2), 0);//left wall
	groundBody->CreateFixture(&myFixtureDef);
	polygonShape.SetAsBox( 1, ALTO_SIM/2, b2Vec2(ANCHO_SIM+1, ALTO_SIM/2), 0);//right wall
	groundBody->CreateFixture(&myFixtureDef);

	//creo megaman, por ahora caja
	//body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(ANCHO_SIM/2, ALTO_SIM/2);
	bodyDef.fixedRotation=true;
	bodyDef.bullet = true;
	b2Body* body = world.CreateBody(&bodyDef);
	//shape
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(3, 3);
	//fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1;
	fixtureDef.friction=0;
	fixtureDef.restitution=0;
	body->CreateFixture(&fixtureDef);

	megaman=body;
}

MyLevel::~MyLevel() {
	// TODO Auto-generated destructor stub
}

/*informs whether the thread is(should be) running*/
bool MyLevel::isRunning(){
	Lock l(runningMutex);
	return running;
}

template <typename T>
std::string numeroATexto(T numero) {
	std::stringstream ss;
	ss << numero;
	return ss.str();
}

/*transforms box2d position to client position format*/
std::string MyLevel::posToString(b2Vec2 pos){
	int p1x = 5;
	int p1y = 5;
	int p2x = pos.x *SCALE;
	int p2y = (ALTO_SIM-pos.y) *SCALE;
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
	float32 timeStep = 1.0f / STEPS_PER_SECOND;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	while(isRunning()){
		world.Step(timeStep, velocityIterations, positionIterations);
		//todo si jugadores pasan mitad pantalla mover
		//todo informar de todos los cambios
		std::string msj=posToString(getPosMegaman());
		game->notificar(new EnvioMensaje(msj,0));
		usleep(timeStep* 1000000 );
	}
}

/*stops physics simulation after current frames is proccessed*/
void MyLevel::stop(){
	Lock l(runningMutex);
	running=false;
}

/*makes the megaman move according to the input*/
void MyLevel::moveMegaman(char boton){
	switch(boton){
	case 'a':{
		LOG(INFO)<<"moviendo megaman con: "<<boton;
		b2Vec2 vel = megaman->GetLinearVelocity();
		vel.x=-10;
		megaman->SetLinearVelocity(vel);
		break;
	}
	case 'w':{
		LOG(INFO)<<"moviendo megaman con: "<<boton;
		b2Vec2 vel = megaman->GetLinearVelocity();

		vel.y =0.50* (-world.GetGravity().y);//upwards - don't change x velocity
		megaman->SetLinearVelocity( vel );
		break;
	}
	case 'd':{
		LOG(INFO)<<"moviendo megaman con: "<<boton;
		b2Vec2 vel = megaman->GetLinearVelocity();
		vel.x=10;
		megaman->SetLinearVelocity(vel);
		break;
	}
	case 's':{
		LOG(INFO)<<"moviendo megaman con: "<<boton;
		b2Vec2 vel = megaman->GetLinearVelocity();
		vel.x=0;//stop moving sideways
		megaman->SetLinearVelocity(vel);
		break;
	}
	default: break;
	}
}

/*returns the vector postition of megaman according to box2d simulation*/
b2Vec2 MyLevel::getPosMegaman(){
	return megaman->GetPosition();
}
