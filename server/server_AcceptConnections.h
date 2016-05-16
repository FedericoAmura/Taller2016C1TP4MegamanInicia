/*
 * server_AcceptConnections.h
 *
 *  Created on: Apr 21, 2016
 *      Author: nicolas
 */

#ifndef SERVER_SERVER_ACCEPTCONNECTIONS_H_
#define SERVER_SERVER_ACCEPTCONNECTIONS_H_

#include "../common/common_Observador.h"
#include "../common/common_Thread.h"
#include "../server/server_ServerSocket.h"


class AcceptConnections: public Thread {
public:
	explicit AcceptConnections(ServerSocket* server,Observador* juego);
	virtual ~AcceptConnections();
	virtual void run();

private:
	ServerSocket* server;
	Observador* juego;
};

#endif /* SERVER_SERVER_ACCEPTCONNECTIONS_H_ */
