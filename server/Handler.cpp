/*
 * common_Handler.cpp
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#include "Handler.h"

#include <sstream>
#include <string>
#include "Evento.h"
#include "Juego.h"
#include <glog/logging.h>
#include "CommunicationCodes.h"

Handler::Handler(Juego* j):juego(j){}

Handler::~Handler() {}

/*************************************************/
/*constructor por herencia*/
AceptarConeccion::AceptarConeccion(Juego* j):Handler(j){}

AceptarConeccion::~AceptarConeccion() {}

void AceptarConeccion::handle(Evento* e){
	NuevaConeccion* evento=static_cast<NuevaConeccion*>(e);//todo error si no es
	juego->aniadirCliente(evento->getDescriptor());
}

/*************************************************/
RecibirMensaje::RecibirMensaje(Juego* j):Handler(j){}

RecibirMensaje::~RecibirMensaje() {}

void RecibirMensaje::moverPersonaje(int direccion){
	if (KEY_UP == direccion) juego->getLevel()->moveMegaman('w');
	if (KEY_RIGHT == direccion) juego->getLevel()->moveMegaman('d');
	if (KEY_DOWN == direccion) juego->getLevel()->moveMegaman('s');
	if (KEY_LEFT == direccion) juego->getLevel()->moveMegaman('a');
}

void RecibirMensaje::handle(Evento* e){
	MensajeRecibido* evento= (MensajeRecibido*) e;
	int procedencia= evento->getReceptor();

	if (evento->getMensaje().substr(0,1).compare("1") == 0){
		LOG(INFO)<<"mensaje recibido: "<< evento->getMensaje() <<"	desde: "<<procedencia;
		moverPersonaje(atoi(evento->getMensaje().substr(2,1).c_str()));
	}
}

/*************************************************/
EnviarMensaje::EnviarMensaje(Juego* j):Handler(j){}

EnviarMensaje::~EnviarMensaje() {}

void EnviarMensaje::handle(Evento* e){
	EnvioMensaje* evento= (EnvioMensaje*) e;
	std::string mensaje=evento->getMensaje();
	int destino=evento->getDestino();
	juego->enviarA(mensaje,destino);
}
