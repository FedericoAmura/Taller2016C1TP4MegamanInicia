/*
 * server_AcceptConnections.cpp
 *
 *  Created on: Apr 21, 2016
 *      Author: nicolas
 */

#include "../server/server_AcceptConnections.h"

#include <iostream>
#include <vector>
#include <glog/logging.h>

AcceptConnections::AcceptConnections(ServerSocket* server,Observador* juego) :
server(server),juego(juego){}


AcceptConnections::~AcceptConnections() {}

/*acepta conecciones hasta que  hallan el maximo de conecciones,
 * en cuyo caso espera una cantidad de tiempo hasta volver intentar aceptar conecciones
 * El thread termina al cerrar el socket*/
void AcceptConnections::run(){
	bool continuar=true;
	LOG(INFO)<<"inicio thread de aceptar conecciones";
	while(continuar){
		int descriptor = server->accept();
		if (descriptor == -1) {
			continuar = false;
		} else {
			LOG(INFO)<<"coneccion entrante";
			juego->notificar(new NuevaConeccion(descriptor));
		}
	}
	LOG(INFO)<<"fin thread de aceptar conecciones";
}
