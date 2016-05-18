/*
 * common_Evento.cpp
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#include "Evento.h"

#include <string>

Evento::Evento():id(0) {}

Evento::~Evento() {}

int Evento::getId(){
	return id;
}

/***************************************************/
NuevaConeccion::NuevaConeccion(int descriptor):descriptor(descriptor){
	id=1;
}

NuevaConeccion::~NuevaConeccion(){}

int NuevaConeccion::getDescriptor(){
	return descriptor;
}
/***************************************************/
MensajeRecibido::MensajeRecibido(std::string data,int receptor):
		data(data),receptor(receptor){
	id=2;
}

MensajeRecibido::~MensajeRecibido(){}

std::string MensajeRecibido::getMensaje(){
	return data;
}

int MensajeRecibido::getReceptor(){
	return receptor;
}
/***************************************************/
EnvioMensaje::EnvioMensaje(std::string data,int dest):data(data),destino(dest){
	id=3;
}

EnvioMensaje::~EnvioMensaje(){}

std::string EnvioMensaje::getMensaje(){
	return data;
}

int EnvioMensaje::getDestino(){
	return destino;
}
