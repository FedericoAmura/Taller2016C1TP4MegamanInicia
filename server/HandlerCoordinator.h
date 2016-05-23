/*
 * server_HandlerCoordinator.h
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#ifndef SERVER_HANDLERCOORDINATOR_H_
#define SERVER_HANDLERCOORDINATOR_H_

#include <map>

#include "Evento.h"
#include "Observador.h"
#include "Handler.h"

class Handler;//forward declaration

class HandlerCoordinator {
	std::map<int,Handler*> handlers;
	Observador* game;

public:
	explicit HandlerCoordinator(Observador* juego);
	virtual ~HandlerCoordinator();
	//todo consider set by event
	void setHandler(int id, Handler* handler);
	void handle(Evento* e);
};
#endif /* SERVER_HANDLERCOORDINATOR_H_ */
