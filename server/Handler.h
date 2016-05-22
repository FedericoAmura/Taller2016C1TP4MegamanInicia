/*
 * common_Handler.h
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#ifndef SERVER_HANDLER_H_
#define SERVER_HANDLER_H_

#include "Evento.h"

class Juego;//forward declaration

/*clase abstracta, deben ser functors*/
class Handler {
public:
	explicit Handler(Juego* j);
	virtual ~Handler();
	virtual void handle(Evento* e)=0;

protected:
	Juego* juego;
};

/*************************************************/
class AceptarConeccion: public Handler{
public:
	explicit AceptarConeccion(Juego* j);
	virtual ~AceptarConeccion();
	void handle(Evento* e);
};

/*************************************************/
class RecibirMensaje: public Handler{
private:
	int p1x;
	int p1y;
	int p2x;
	int p2y;
public:
	explicit RecibirMensaje(Juego* j);
	virtual ~RecibirMensaje();
	void handle(Evento* e);
};

/*************************************************/
class EnviarMensaje: public Handler{
public:
	explicit EnviarMensaje(Juego* j);
	virtual ~EnviarMensaje();
	void handle(Evento* e);
};
#endif /* SERVER_HANDLER_H_ */
