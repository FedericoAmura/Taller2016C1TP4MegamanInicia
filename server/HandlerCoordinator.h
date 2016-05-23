/*
 * server_HandlerCoordinator.h
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#ifndef SERVER_HANDLERCOORDINATOR_H_
#define SERVER_HANDLERCOORDINATOR_H_

#include <map>

#include "Event.h"
#include "Handler.h"
#include "Observer.h"

class Handler;//forward declaration

class HandlerCoordinator {
	std::map<int,Handler*> handlers;
	Observer* game;

public:
	explicit HandlerCoordinator(Observer* juego);
	virtual ~HandlerCoordinator();
	//todo consider set by event
	void setHandler(int id, Handler* handler);
	void handle(Event* e);
};
#endif /* SERVER_HANDLERCOORDINATOR_H_ */
