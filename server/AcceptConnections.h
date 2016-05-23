/*
 * server_AcceptConnections.h
 *
 *  Created on: Apr 21, 2016
 *      Author: nicolas
 */

#ifndef SERVER_ACCEPTCONNECTIONS_H_
#define SERVER_ACCEPTCONNECTIONS_H_

#include "Observer.h"
#include "ServerSocket.h"
#include "Thread.h"


class AcceptConnections: public Thread {
public:
	explicit AcceptConnections(ServerSocket* server,Observer* juego);
	virtual ~AcceptConnections();
	virtual void run();

private:
	ServerSocket* server;
	Observer* juego;
};

#endif /* SERVER_ACCEPTCONNECTIONS_H_ */
