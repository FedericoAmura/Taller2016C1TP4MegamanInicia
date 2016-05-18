/*
 * common_SendThread.cpp
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#include "../server/SendRecvThread.h"

#include <string>
#include <unistd.h>
#include <glog/logging.h>
#include <sstream>

#include "Evento.h"
#include "Socket.h"

#define TIMEOUT 10000

SendThread::SendThread(Socket* s):socket(s) {}

SendThread::~SendThread() {}


void SendThread::run(){
	while(socket->estaAbierto()){
		//todo lock
		if(!aEnviar.empty()){
			std::string mensaje=aEnviar.front();
			aEnviar.pop();
			mensaje.append("\n");
			socket->send((char*)mensaje.c_str(),mensaje.size());
			LOG(INFO)<<"enviado msg: "<<mensaje;
		}else{
			usleep(TIMEOUT);
		}
	}
}

/*aniade a la cola de envios data. data debe ser string sin fin de linea*/
void SendThread::enviar(char* data){
	//todo lock
	std::string s(data);
	aEnviar.push(s);
}

/******************************************************************************/
RecvThread::RecvThread(Socket* s, Observador* o):socket(s), observador(o) {}

RecvThread::~RecvThread() {}

/*recibe de forma constante lineas se terminadas por un \n (sin espacios)
 * y notifica al observador, dandole el mensaje y su procedencia
 * en un unico string, separados por un espacio*/
void RecvThread::run(){
	while(socket->estaAbierto()){
		std::stringstream recibido;
		char caracter;
		bool continuar=true;
		bool recibi=false;
		do{
			if(socket->recieve(&caracter,1)){
				recibi=true;
				if(caracter!=10)
					recibido<<caracter;
				else
					continuar=false;
			}else{
				continuar=false;
				socket->shutdown();
			}
		}while(continuar);
		if(recibi){
			std::string recvStr=recibido.str();
			observador->notificar(new MensajeRecibido(recvStr,socket->descriptor));
		}else{
			usleep(TIMEOUT);
		}
	}
}
