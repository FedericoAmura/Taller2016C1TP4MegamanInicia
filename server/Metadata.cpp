/*
 * Metadata.cpp
 *
 *  Created on: Jun 12, 2016
 *      Author: nicolas
 */

#include "Metadata.h"
#include "Game.h"
#include "Model/Stat.h"
#include <vector>

Metadata::Metadata(Game* game)
:game(game){}

Metadata::~Metadata() {
	std::vector<ClientData*>::iterator dataIt=clientsData.begin();
	for(; dataIt!=clientsData.end(); dataIt++){
		delete (*dataIt);
	}
}

void Metadata::addClient(int descriptor, int number) {
	Lock l(clientsMutex);
	clientsData.push_back(new ClientData(descriptor,number,game));
}

void Metadata::removeClient(int descriptor) {
	Lock l(clientsMutex);
	bool found=false;
	std::vector<ClientData*>::iterator dataIt=clientsData.begin();
	for(; dataIt!=clientsData.end() && !found; dataIt++){
		if((*dataIt)->getDescriptor()==descriptor){
			dataIt=clientsData.erase(dataIt);
			found=true;
		}
	}
}

int Metadata::getNumberOfClients() {
	return clientsData.size();
}

/*attempts to get nth client , if it fails return nullptr*/
ClientData* Metadata::getClient(int number) {
	Lock l(clientsMutex);
	if((uint)number>clientsData.size()){
		return nullptr;
	}else{
		return clientsData[number-1];
	}
}

/***************************************************************/
ClientData::ClientData(int desc, int number, Game* game)
:descriptor(desc),
 clientNumber(number),
 game(game),
 lives(5,3){}

ClientData::~ClientData() {
}

int ClientData::getClientNumber() {
	return clientNumber;
}

int ClientData::getDescriptor() {
	return descriptor;
}

Stat<int>& ClientData::getLives() {
	return lives;
}

Game* ClientData::getGame() {
	return game;
}
