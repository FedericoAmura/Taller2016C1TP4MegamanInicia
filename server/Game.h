/*
 * server_Juego1.h
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#ifndef SERVER_GAME_H_
#define SERVER_GAME_H_

#include <map>
#include <string>

#include "Event.h"
#include "HandlerCoordinator.h"
#include "Socket.h"
#include "Model/MyLevel.h"
#include "Observer.h"
#include "../common/Thread.h"
#include "ThreadQueue.h"
class Server;//forward declaration

class Game:public Thread,public Observer{
	Mutex goOnMutex;
	bool goOn;
	Server* server;
	ThreadQueue<Event*> eventQueue;
	HandlerCoordinator manager;
	MyLevel* level;

	Mutex clientsMutex;
	std::map<int,Socket*> clients;
	int firstClient;

public:
	explicit Game(Server* server);
	virtual ~Game();
	virtual void run();
	void notify(Event* e);
	void stop();

	bool levelChosen();
	void selectLevel(int levelId,int client);
	void stopLevel();
	MyLevel* getLevel();
	void movePlayer(int keyPressed,int source);

	void addClient(int descriptor);
	void sendTo(std::string data, int destino);
	void removeClient(int descriptor);
private:
	bool isntStopped();
};

#endif /* SERVER_GAME_H_ */
