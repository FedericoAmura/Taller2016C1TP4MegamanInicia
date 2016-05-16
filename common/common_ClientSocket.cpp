/*
 * ClientSocket.cpp
 *
 *  Created on: Apr 18, 2016
 *      Author: nicolas
 */

#include "../common/common_ClientSocket.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include<iostream>
#include <glog/logging.h>
#include <errno.h>
#include <unistd.h>

#include <stdexcept>

/*pre: ip adress en formato "humano", port es short comun,sin htons
 * post:crea cliente para conectarse a ipAdress en port*/
ClientSocket::ClientSocket(Observador* modelo,const char* ipAdress,int port)
:Socket(modelo){
	server.sin_addr.s_addr = inet_addr(ipAdress);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
}

/*el cierre lo maneja clase padre*/
ClientSocket::~ClientSocket() {
	//potencialmente se puede sacar, pero podria no tener tiempo
	//de enviar el mensaje antes de apagar el socket
	usleep(200000);
}

//todo considerar obtener ip y puerto aca
/*intenta conectar el cliente a la ip y puerto previamente asignados*/
void ClientSocket::conectar(){
	struct sockaddr_in server=this->server;
	struct sockaddr_in* server0 = &(server);
	struct sockaddr* sockaddr0 = (struct sockaddr*) server0;
	if (connect(descriptor, sockaddr0, sizeof(server))) {
		LOG(FATAL)<<"error de coneccion: "<<errno;
		throw std::runtime_error("Error:coneccion socket");
	}
	iniciarComunicaciones();
}



