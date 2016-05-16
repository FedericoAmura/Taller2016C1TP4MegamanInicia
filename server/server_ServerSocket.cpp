/*
 * Server.cpp
 *
 *  Created on: Apr 18, 2016
 *      Author: nicolas
 */

#include "../server/server_ServerSocket.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdexcept>
#include <stdexcept>
#include <errno.h>
#include <cstring>
#include <iostream>

ServerSocket::ServerSocket(int port){
	descriptor=socket(AF_INET,SOCK_STREAM,0);
	if(descriptor<0){
		throw std::runtime_error("Error: creacion socket");
	}
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
}

/*el cierre lo maneja clase padre*/
ServerSocket::~ServerSocket() {
	this->shutdown();
}

void ServerSocket::listen(){
	int result= ::listen(descriptor,3);
	if(result== -1) throw std::runtime_error("Error: listen");
}

void ServerSocket::bind(){
	int yes=1;
	// lose the pesky "Address already in use" error message
	if (setsockopt(descriptor,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
		throw std::runtime_error("Error: bind");
	}
	int result = ::bind(descriptor,
			(struct sockaddr*) &(server),sizeof(server));
	if(result<0){
		std::cout<<std::strerror(errno)<<"\n";
		throw std::runtime_error("Error: bind");
	}
}

/*devuelve el descriptor aceptado o un error*/
int ServerSocket::accept(){
	return ::accept(descriptor, NULL, NULL);
}

/*apaga el socket*/
void ServerSocket::shutdown(){
	::shutdown(descriptor,SHUT_RDWR);
}

