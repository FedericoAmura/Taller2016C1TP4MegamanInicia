/*
 * common_Evento.cpp
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#include <string>
#include "Event.h"

Event::Event():id(0) {}

Event::~Event() {}

int Event::getId(){
	return id;
}

/***************************************************/
NewConnection::NewConnection(int descriptor):descriptor(descriptor){
	id=1;
}

NewConnection::~NewConnection(){}

int NewConnection::getDescriptor(){
	return descriptor;
}
/***************************************************/
MessageRecieved::MessageRecieved(std::string data,int receptor):
		data(data),receptor(receptor){
	id=2;
}

MessageRecieved::~MessageRecieved(){}

std::string MessageRecieved::getMessage(){
	return data;
}

int MessageRecieved::getReceptor(){
	return receptor;
}
/***************************************************/
/*dest es el numero descriptor del cliente.
 * data es string no terminado en \n con caracteres comunes nada mas*/
MessageSent::MessageSent(std::string data,int dest):data(data),destination(dest){
	id=3;
}

MessageSent::~MessageSent(){}

std::string MessageSent::getMessage(){
	return data;
}

int MessageSent::getDestination(){
	return destination;
}

/***************************************************/
ConnectionEnded::ConnectionEnded(int client):descriptor(client) {
	id=4;
}

ConnectionEnded::~ConnectionEnded() {}

int ConnectionEnded::getClient() {
	return descriptor;
}

/***************************************************/
LevelFinished::LevelFinished(int condition,int id)
: condition(condition),
  levelId(id){
	this->id=5;
}

LevelFinished::~LevelFinished() {}

int LevelFinished::getCondition() {
	return condition;
}

int LevelFinished::getLevelId(){
	return levelId;
}
