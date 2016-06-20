/*
 * Metadata.h
 *
 *  Created on: Jun 12, 2016
 *      Author: nicolas
 */

#ifndef SERVER_METADATA_H_
#define SERVER_METADATA_H_

#include "Model/Stat.h"
#include "../common/Thread.h"
#include <vector>
class Game;
class ClientData;

class Metadata {
	Game* game;
	std::vector<ClientData*> clientsData;
	Mutex clientsMutex;

public:
	Metadata(Game* game);
	virtual ~Metadata();
	void addClient(int descriptor, int number);
	void removeClient(int descriptor);
	int getNumberOfClients();
	ClientData* getClient(int number);
};

class ClientData{
	int descriptor;
	int clientNumber;
	Game* game;
	Stat<int> lives;
public:
	ClientData(int desc, int number, Game* game);
	virtual ~ClientData();
	int getClientNumber();
	void setClientNumber(int newNumber);
	int getDescriptor();
	Stat<int>& getLives();
	Game* getGame();
};
#endif /* SERVER_METADATA_H_ */
