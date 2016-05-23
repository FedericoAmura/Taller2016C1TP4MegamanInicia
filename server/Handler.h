/*
 * common_Handler.h
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#ifndef SERVER_HANDLER_H_
#define SERVER_HANDLER_H_

#include "Event.h"

class Game;//forward declaration

/*clase abstracta, deben ser functors*/
class Handler {
public:
	explicit Handler(Game* j);
	virtual ~Handler();
	virtual void handle(Event* e)=0;

protected:
	Game* juego;
};

/*************************************************/
class AceptarConeccion: public Handler{
public:
	explicit AceptarConeccion(Game* j);
	virtual ~AceptarConeccion();
	void handle(Event* e);
};

/*************************************************/
class RecibirMensaje: public Handler{
public:
	explicit RecibirMensaje(Game* j);
	virtual ~RecibirMensaje();
	void handle(Event* e);
	void moverPersonaje(int direccion);
};

/*************************************************/
class EnviarMensaje: public Handler{
public:
	explicit EnviarMensaje(Game* j);
	virtual ~EnviarMensaje();
	void handle(Event* e);
};
#endif /* SERVER_HANDLER_H_ */
