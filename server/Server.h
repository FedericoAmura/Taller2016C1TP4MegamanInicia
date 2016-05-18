/*
 * server_Server.h
 *
 *  Created on: Apr 20, 2016
 *      Author: nicolas
 */

#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include "AcceptConnections.h"
#include "ServerSocket.h"
#include "Juego.h"

class Server {
public:
	explicit Server(int port);
	virtual ~Server();
	void correrServer();

private:
	ServerSocket socket;
	Juego juego;
	AcceptConnections aceptador;
};

#endif /* SERVER_SERVER_H_ */
