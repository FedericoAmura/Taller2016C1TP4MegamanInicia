/*
 * common_Handler.cpp
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#include "Handler.h"

#include <sstream>
#include <string>
#include <glog/logging.h>
#include "../common/CommunicationCodes.h"
#include "Event.h"
#include "Game.h"

Handler::Handler(Game* j):juego(j){}

Handler::~Handler() {}

/*************************************************/
/*constructor por herencia*/
AceptarConeccion::AceptarConeccion(Game* j):Handler(j){}

AceptarConeccion::~AceptarConeccion() {}

void AceptarConeccion::handle(Event* e){
	NewConnection* evento=static_cast<NewConnection*>(e);//todo error si no es
	juego->addClient(evento->getDescriptor());
}

/*************************************************/
RecibirMensaje::RecibirMensaje(Game* j):Handler(j){}

RecibirMensaje::~RecibirMensaje() {}

/*todo move to megaman class*/
void RecibirMensaje::moverPersonaje(int direccion){
	if (KEY_UP == direccion) juego->getLevel()->moveMegaman('w');
	if (KEY_RIGHT == direccion) juego->getLevel()->moveMegaman('d');
	if (KEY_DOWN == direccion) juego->getLevel()->moveMegaman('s');
	if (KEY_LEFT == direccion) juego->getLevel()->moveMegaman('a');
}

void RecibirMensaje::handle(Event* e){
	MessageRecieved* evento= (MessageRecieved*) e;
	int procedencia= evento->getReceptor();

	if (evento->getMessage().substr(0,1).compare("1") == 0){
		LOG(INFO)<<"mensaje recibido: "<< evento->getMessage() <<"	desde: "<<procedencia;
		int keyPressed = atoi(evento->getMessage().substr(2, 1).c_str());
		if(keyPressed==7)
			juego->stopLevel();
		else
			moverPersonaje(keyPressed);
	}
}

/*************************************************/
EnviarMensaje::EnviarMensaje(Game* j):Handler(j){}

EnviarMensaje::~EnviarMensaje() {}

void EnviarMensaje::handle(Event* e){
	MessageSent* evento= (MessageSent*) e;
	std::string mensaje=evento->getMessage();
	int destino=evento->getDestination();
	juego->sendTo(mensaje,destino);
}
