/*
 * common_Handler.cpp
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#include "Handler.h"

#include <sstream>
#include <string>
#include <glog/logging.h>
#include "../common/CommunicationCodes.h"
#include "Event.h"
#include "Game.h"
#include "../common/MegamanBeginsConstants.h"

Handler::Handler(Game* j):game(j){}

Handler::~Handler() {}

/*************************************************/
/*constructor por herencia*/
AcceptConnection::AcceptConnection(Game* j):Handler(j){}

AcceptConnection::~AcceptConnection() {}

void AcceptConnection::handle(Event* e){
	NewConnection* evento=static_cast<NewConnection*>(e);//todo error si no es
	game->addClient(evento->getDescriptor());
}

/*************************************************/
RecvMessage::RecvMessage(Game* j):Handler(j){}

RecvMessage::~RecvMessage() {}

void RecvMessage::handle(Event* e){
	MessageRecieved* evento= (MessageRecieved*) e;
	int procedencia= evento->getReceptor();
	std::stringstream msj(evento->getMessage());
	int cod;
	msj>>cod;
	//LOG(INFO)<<"mensaje recibido: "<< evento->getMessage() <<"	desde: "<<procedencia;
	switch(cod){
	case 1:/*key presed*/
		uint keyState;
		msj>>keyState;
		if(keyState & KEY_ESC_ID)
			game->stopLevel();
		else
			game->movePlayer(keyState,procedencia);
		break;
	case 2:/*select level*/
		int levelId;
		msj>>levelId;
		game->selectLevel(levelId,procedencia);
		break;
	}
}

/*************************************************/
SendMessage::SendMessage(Game* j):Handler(j){}

SendMessage::~SendMessage() {}

void SendMessage::handle(Event* e){
	MessageSent* evento= (MessageSent*) e;
	std::string mensaje=evento->getMessage();
	int destino=evento->getDestination();
	game->sendTo(mensaje,destino);
}

/*************************************************/
DisconnectClient::DisconnectClient(Game* j):Handler(j) {}

DisconnectClient::~DisconnectClient() {}

void DisconnectClient::handle(Event* e) {
	ConnectionEnded* event= (ConnectionEnded*)e;
	game->removeClient(event->getClient());
}

/*************************************************/
FinishLevel::FinishLevel(Game* j):Handler(j) {}

FinishLevel::~FinishLevel() {}

void FinishLevel::handle(Event* e) {
	//LevelFinished* event= (LevelFinished*)e;
	//event->getCondition();
	game->stopLevel();
}
