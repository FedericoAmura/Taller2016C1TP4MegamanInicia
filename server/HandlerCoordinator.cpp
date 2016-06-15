/*
 * server_HandlerCoordinator.cpp
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#include "HandlerCoordinator.h"

#include <map>
#include <algorithm>
#include <stdexcept>
#include <glog/logging.h>

HandlerCoordinator::HandlerCoordinator(Observer* juego):game(juego){
}

HandlerCoordinator::~HandlerCoordinator() {
	std::map<int,Handler*>::iterator handlerIt=handlers.begin();
	for(; handlerIt!=handlers.end(); handlerIt++){
		delete handlerIt->second;
	}
}

/*aniade handler para el id de evento. Si ya existe lo reemplaza*/
void HandlerCoordinator::setHandler(int id, Handler* handler){
	//todo lock
	std::map<int,Handler*>::iterator position= handlers.find(id);
	if(position!=handlers.end()){
		delete position->second;
		handlers.erase(position);
	}
	handlers[id]=handler;
}

/*assigns handler to event, then starts thread to handle it*/
void HandlerCoordinator::handle(Event*e){
	std::map<int,Handler*>::iterator handler= handlers.find(e->getId());
	if(handler!=handlers.end()){
		try{
			(handler->second)->handle(e);
		}catch(std::runtime_error& err){
			//if event handler fails I record but dont blow up
			LOG(ERROR)<<err.what();
		}
	}
}
