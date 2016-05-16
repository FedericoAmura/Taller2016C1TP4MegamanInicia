/*
 * ClientSocket.h
 *
 *  Created on: Apr 18, 2016
 *      Author: nicolas
 */

#ifndef COMMON_COMMON_CLIENTSOCKET_H_
#define COMMON_COMMON_CLIENTSOCKET_H_

#include<arpa/inet.h>

#include "../common/common_Observador.h"
#include "../common/common_Socket.h"


class ClientSocket: public Socket{
public:
	ClientSocket(Observador* modelo,const char* ipAdress,int port);
	virtual ~ClientSocket();
	void conectar();

private:
	struct sockaddr_in server;
};

#endif /* COMMON_COMMON_CLIENTSOCKET_H_ */
