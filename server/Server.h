/*
 * server_Server.h
 *
 *  Created on: Apr 20, 2016
 *      Author: nicolas
 */

#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include "AcceptConnections.h"
#include "Game.h"
#include "ServerSocket.h"
#include <string>
#include <fstream>

class Server {
public:
	explicit Server(int port);
	virtual ~Server();
	void runServer();

private:
	ServerSocket socket;
	Game game;
	AcceptConnections acceptor;
	std::string getFileContents(std::ifstream& File);
	void printAscciArt();
};

#endif /* SERVER_SERVER_H_ */
