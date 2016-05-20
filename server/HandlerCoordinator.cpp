/*
 * server_HandlerCoordinator.cpp
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#include "HandlerCoordinator.h"

#include <map>
#include <vector>
#include <unistd.h>
#include <algorithm>
#include <stdexcept>
#include <glog/logging.h>

#define JOINER_WAIT 100000 //useg

HandlerCoordinator::HandlerCoordinator(Observador* juego):
game(juego), joiner(this){
	joiner.start();
	HandlerThread::setJoiner(&joiner);
}

HandlerCoordinator::~HandlerCoordinator() {
	joiner.stop();
	joiner.join();

	//liberar handlers map
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
void HandlerCoordinator::handle(Evento*e){
	std::map<int,Handler*>::iterator posicion= handlers.find(e->getId());
	if(posicion!=handlers.end()){
		try{
			Lock l(threadsMutex);
			Thread* t= new HandlerThread(posicion->second,e);
			threads.push_back(t);
			t->start();
		}catch(std::runtime_error& e){
			//if event handler fails I record but dont blow up
			LOG(ERROR)<<e.what();
			LOG(ERROR)<<"Threads de handlers corriendo: "<<threads.size();
		}
	}
}

/*joins,destroys and removes thread*/
void HandlerCoordinator::killThread(Thread* t){
	std::vector<Thread*>::iterator position;
	Lock l(threadsMutex);
	position= find(threads.begin(),threads.end(),t);
	threads.erase(position);
	t->join();
	delete t;
}

/**********************************************************/
JoinerThread::JoinerThread(HandlerCoordinator* h):coordinator(h),stopped(false){}

JoinerThread::~JoinerThread(){}

/*kill thread until its asked to stop*/
void JoinerThread::run(){
	while(proceed()){
		if(true){
			Lock l(queueMutex);
			while(!queue.empty()){
				coordinator->killThread(queue.front());
				queue.pop();
			}
		}//if to separete sleep from lock
		usleep(JOINER_WAIT);
	}
}

/*returns true if thread shouldnt stop*/
bool JoinerThread::proceed(){
	Lock l(stoppedMutex);
	return !stopped;
}

/*stops the thread*/
void JoinerThread::stop(){
	Lock l(stoppedMutex);
	stopped=true;
}

/*adds thread to kill queue*/
void JoinerThread::push(Thread* t){
	Lock l(queueMutex);
	queue.push(t);
}

/**********************************************************/
JoinerThread* HandlerThread::joiner=0;//static initialization

HandlerThread::HandlerThread(Handler* h, Evento* e):event(e),handler(h){}

HandlerThread::~HandlerThread(){}

/*Sets joiner for resource management.
 * Should only be uesd once, at start of program*/
void HandlerThread::setJoiner(JoinerThread* j){
	joiner=j;
}

/*handles event, then destroys it*/
void HandlerThread::run(){
	handler->handle(event);
	delete event;
	killMe();
}

/*add me to list to kill*/
void HandlerThread::killMe(){
	joiner->push(this);
}
