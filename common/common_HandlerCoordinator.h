/*
 * server_HandlerCoordinator.h
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#ifndef COMMON_COMMON_HANDLERCOORDINATOR_H_
#define COMMON_COMMON_HANDLERCOORDINATOR_H_

#include <map>
#include <vector>

#include "../common/common_Evento.h"
#include "../common/common_Handler.h"
#include "../common/common_Observador.h"
#include "../common/common_Thread.h"

class Handler;//forward declaration

class HandlerCoordinator {
	std::map<int,Handler*> handlers;
	Observador* juego;
	std::vector<Thread*> threads;

public:
	explicit HandlerCoordinator(Observador* juego);
	virtual ~HandlerCoordinator();
	//todo considearar poder setear con un evento y handler
	void setearHandler(int id, Handler* handler);
	void handle(Evento* e);
};

/*********************************************************/
class HandlerThread: public Thread{
	Evento* evento;
	Handler* handler;
public:
	HandlerThread(Handler* h,Evento* e);
	virtual ~HandlerThread();
	virtual void run();
};
#endif /* COMMON_COMMON_HANDLERCOORDINATOR_H_ */
