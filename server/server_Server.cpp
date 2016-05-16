/*
 * server_Server.cpp
 *
 *  Created on: Apr 20, 2016
 *      Author: nicolas
 */

#include "../server/server_Server.h"

#include <iostream>
#include <string>
#include <queue>
#include <glog/logging.h>

#include "../server/server_AcceptConnections.h"

/*pre: puerto es int comun, no hace falta aplicarle htons antes.
 *post: crea el server y lo deja listo para aceptar.
 * En caso que el socket aceptor no se cree lanza excepcion SocketCreacion*/
Server::Server(int port): socket(port),juego(this),aceptador(&socket,&juego){
	socket.bind();
	socket.listen();

	aceptador.start();
	juego.start();
}

/*libera los recursos de los threads
 *de cerrarlo se encarga la clase padre*/
Server::~Server() {
	socket.shutdown();

	aceptador.join();
	juego.join();
}

/*acepta clientes y maneja datos hasta ingresar q por entrada*/
void Server::correrServer() {
	LOG(INFO)<<"server iniciado";
	bool continuar=true;
	do{
		std::string entrada;
		getline(std::cin,entrada);
		if(entrada=="q")
			continuar=false;
	}while(continuar);
	/*informe de cierre a clientes*/
	juego.notificar(new EnvioMensaje("chau",0));
	sleep(1);
	/*cierre*/
	juego.cerrar();
	LOG(INFO)<<"server finalizado";
}
