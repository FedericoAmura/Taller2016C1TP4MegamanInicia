/*
 * server_Juego1.h
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#ifndef SERVER_GAME_H_
#define SERVER_GAME_H_

#include <queue>

#include <map>
#include <string>

#include "Event.h"
#include "HandlerCoordinator.h"
#include "Socket.h"
#include "Model/MyLevel.h"
#include "Observer.h"
#include "Thread.h"
class Server;//forward declaration

class Game:public Thread,public Observer{
	Mutex goOnMutex;
	bool goOn;
	Server* server;
	Mutex queueMutex;
	std::queue<Event*> eventQueue;
	HandlerCoordinator manager;
	MyLevel* level;

	/*candidato a extraer*/
	Mutex clientsMutex;
	std::map<int,Socket*> clients;
	int firstClient;

public:
	explicit Game(Server* server);
	virtual ~Game();
	virtual void run();
	void notify(Event* e);
	void stop();

	MyLevel* getLevel();
	void selectLevel(int levelId);
	void stopLevel();

	void addClient(int descriptor);
	void sendTo(std::string data, int destino);
private:
	bool isntStopped();
};

#endif /* SERVER_GAME_H_ */
