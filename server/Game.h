/*
 * server_Juego1.h
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#ifndef SERVER_GAME_H_
#define SERVER_GAME_H_

#include <map>
#include <vector>
#include <string>
#include <queue>

#include "Event.h"
#include "HandlerCoordinator.h"
#include "Socket.h"
#include "Model/MyLevel.h"
#include "Observer.h"
#include "../common/Thread.h"
#include "ThreadQueue.h"
#include "Metadata.h"

using std::map;
using std::vector;
using std::string;

class Server;//forward declaration

class Game: public Thread, public Observer{
	Mutex goOnMutex;
	bool goOn;
	Server* server;
	ThreadQueue<Event*> eventQueue;
	HandlerCoordinator manager;
	MyLevel* level;

	Mutex clientsMutex;
	std::map<int,Socket*> clients;
	std::map<int,int> clientNum;
	Metadata metadata;
	std::queue<int> availableClientNumbers;

public:
	int firstClient;
	explicit Game(Server* server);
	virtual ~Game();
	virtual void run();
	void notify(Event* e);
	void stop();

	bool levelChosen();
	void selectLevel(int levelId,int client);
	void stopLevel();
	MyLevel* getLevel();
	void movePlayer(uint keyState,int source);

	void addClient(int descriptor);
	void sendTo(std::string data, int destino);
	void removeClient(int descriptor);
	void resetClientLives();

private:
	bool isntStopped();
	vector<string> findFilesInDir();
	map<uint, string> getLevelFiles();
};

#endif /* SERVER_GAME_H_ */
