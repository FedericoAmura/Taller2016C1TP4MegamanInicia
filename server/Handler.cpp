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
#include "Evento.h"
#include "Juego.h"

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

void RecibirMensaje::handle(Evento* e){
	MensajeRecibido* evento= (MensajeRecibido*) e;
	int procedencia= evento->getReceptor();
	LOG(INFO)<<"mensaje recibido: "<< evento->getMensaje() <<" de: "<<procedencia;

	/*test*/
	std::stringstream ss2;
	ss2<<"hola_cliente!_para_mi_sos_ "<<procedencia;
	juego->notificar(new EnvioMensaje(ss2.str(),procedencia));
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
