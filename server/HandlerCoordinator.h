/*
 * server_HandlerCoordinator.h
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#ifndef SERVER_HANDLERCOORDINATOR_H_
#define SERVER_HANDLERCOORDINATOR_H_

#include <map>
#include <vector>
#include <queue>

#include "Evento.h"
#include "Observador.h"
#include "Thread.h"
#include "Handler.h"

class Handler;//forward declaration
class HandlerCoordinator;//forward declaration

class JoinerThread: public Thread{
	Mutex queueMutex;
	std::queue<Thread*> queue;
	HandlerCoordinator* coordinator;
	Mutex stoppedMutex;
	bool stopped;
	bool proceed();

public:
	JoinerThread(HandlerCoordinator* h);
	virtual ~JoinerThread();
	virtual void run();
	void stop();
	void push(Thread* t);
};

/*********************************************************/
class HandlerCoordinator {
	std::map<int,Handler*> handlers;
	Observador* game;
	Mutex threadsMutex;
	std::vector<Thread*> threads;
	JoinerThread joiner;

public:
	explicit HandlerCoordinator(Observador* juego);
	virtual ~HandlerCoordinator();
	//todo consider set by event
	void setHandler(int id, Handler* handler);
	void handle(Evento* e);
	void killThread(Thread* t);
};

/*********************************************************/
class HandlerThread: public Thread{
	static JoinerThread* joiner;
	Evento* event;
	Handler* handler;
	void killMe();

public:
	static void setJoiner(JoinerThread* j);
	HandlerThread(Handler* h,Evento* e);
	virtual ~HandlerThread();
	virtual void run();
};
#endif /* SERVER_HANDLERCOORDINATOR_H_ */
