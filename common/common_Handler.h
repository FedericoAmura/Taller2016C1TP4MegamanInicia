/*
 * common_Handler.h
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#ifndef COMMON_COMMON_HANDLER_H_
#define COMMON_COMMON_HANDLER_H_

#include "../common/common_Evento.h"

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
#endif /* COMMON_COMMON_HANDLER_H_ */
