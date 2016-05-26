/*
 * server_Server.cpp
 *
 *  Created on: Apr 20, 2016
 *      Author: nicolas
 */

#include <iostream>
#include <string>
#include <queue>
#include <glog/logging.h>

#include "Server.h"
#include "AcceptConnections.h"

/*pre: puerto es int comun, no hace falta aplicarle htons antes.
 *post: crea el server y lo deja listo para aceptar.
 * En caso que el socket aceptor no se cree lanza excepcion SocketCreacion*/
Server::Server(int port): socket(port),game(this),acceptor(&socket,&game){
	socket.bind();
	socket.listen();

	acceptor.start();
	game.start();
}

/*libera los recursos de los threads
 *de cerrarlo se encarga la clase padre*/
Server::~Server() {
	socket.shutdown();

	acceptor.join();
	game.join();
}

/*acepta clientes y maneja datos hasta ingresar q por entrada*/
void Server::runServer() {
	LOG(INFO)<<"server iniciado";
	bool continuar=true;
	do{
		std::string entrada;
		getline(std::cin,entrada);
		if(entrada=="q")
			continuar=false;
	}while(continuar);
	/*informe de cierre a clientes*/
	game.notify(new MessageSent("chau",0));
	sleep(1);
	/*cierre*/
	game.stop();
	LOG(INFO)<<"server finalizado";
}
