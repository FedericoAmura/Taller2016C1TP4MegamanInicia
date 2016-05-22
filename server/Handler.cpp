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
RecibirMensaje::RecibirMensaje(Juego* j):Handler(j),
		p1x(25),
		p1y(25),
		p2x(50),
		p2y(50){}

RecibirMensaje::~RecibirMensaje() {}

#define ARRIBA 1
#define DERECHA 2
#define ABAJO 3
#define IZQUIERDA 4

template <typename T>
std::string numeroATexto(T numero) {
	std::stringstream ss;
	ss << numero;
	return ss.str();
}

void moverPersonaje(int direccion, int* px, int* py){
	if ((KEY_UP == direccion) && (*py > 0)) *py = *py - 1;
	if ((KEY_RIGHT == direccion) && (*px < 100)) *px = *px + 1;
	if ((KEY_DOWN == direccion) && (*py < 100)) *py = *py + 1;
	if ((KEY_LEFT == direccion) && (*px > 0)) *px = *px - 1;
}

void RecibirMensaje::handle(Evento* e){
	MensajeRecibido* evento= (MensajeRecibido*) e;
	int procedencia= evento->getReceptor();
	LOG(INFO)<<"mensaje recibido: "<< evento->getMensaje() <<"	desde: "<<procedencia;

	if (evento->getMensaje().substr(0,1).compare("1") == 0){
		moverPersonaje(atoi(evento->getMensaje().substr(2,1).c_str()),&p1x,&p1y);
	}

	//todo hacer que funcione
	moverPersonaje(1+rand()%4,&p2x,&p2y);
	std::string posp1 = "X1:" + numeroATexto(p1x) + "-Y1:" + numeroATexto(p1y);
	std::string posp2 = "X2:" + numeroATexto(p2x) + "-Y2:" + numeroATexto(p2y);
	juego->notificar(new EnvioMensaje(posp1+"/"+posp2,procedencia));
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
