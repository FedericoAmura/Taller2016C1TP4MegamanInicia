/*
 * server_HandlerCoordinator.cpp
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#include "../common/common_HandlerCoordinator.h"

#include <map>
#include <vector>

HandlerCoordinator::HandlerCoordinator(Observador* juego):juego(juego) {}

HandlerCoordinator::~HandlerCoordinator() {
	//liberar handlers
	std::map<int,Handler*>::iterator itMap= handlers.begin();
	for(; itMap!= handlers.end(); itMap++){
		delete itMap->second;
	}
	//liberar threads
	std::vector<Thread*>::iterator itThreads= threads.begin();
	for(; itThreads!= threads.end(); itThreads++){
		(*itThreads)->join();
	}
	itThreads= threads.begin();
	for(; itThreads!= threads.end(); itThreads++){
		delete *itThreads;
	}
}

/*aniade handler para el id de evento. Si ya existe lo reemplaza*/
void HandlerCoordinator::setearHandler(int id, Handler* handler){
	//todo lock
	std::map<int,Handler*>::iterator posicion= handlers.find(id);
	if(posicion!=handlers.end()){
		delete posicion->second;
		handlers.erase(posicion);
	}
	handlers[id]=handler;
}

void HandlerCoordinator::handle(Evento*e){
	std::map<int,Handler*>::iterator posicion= handlers.find(e->getId());
	if(posicion!=handlers.end()){
		Thread* t= new HandlerThread(posicion->second,e);
		threads.push_back(t);
		t->start();
	}
}

/**********************************************************/
HandlerThread::HandlerThread(Handler* h, Evento* e):evento(e),handler(h){}

HandlerThread::~HandlerThread(){}

/*maneja el evento, y al final de esto lo destruye*/
void HandlerThread::run(){
	handler->handle(evento);
	delete evento;
}
