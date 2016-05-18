/*
 * Server.h
 *
 *  Created on: Apr 18, 2016
 *      Author: nicolas
 */

#ifndef SERVER_SERVERSOCKET_H_
#define SERVER_SERVERSOCKET_H_

#include<arpa/inet.h>

class ServerSocket{
public:
	explicit ServerSocket(int port);
	virtual ~ServerSocket();
	void listen();
	void bind();
	int accept();
	void shutdown();

private:
	int descriptor;
	struct sockaddr_in server;
};

#endif /* SERVER_SERVERSOCKET_H_ */
