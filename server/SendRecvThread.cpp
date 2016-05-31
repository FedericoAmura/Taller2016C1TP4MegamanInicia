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

#include "Event.h"
#include "Socket.h"

#define TIMEOUT 10000

SendThread::SendThread(Socket* s):socket(s) {}

SendThread::~SendThread() {}


void SendThread::run(){
	while(socket->estaAbierto()){
		std::string mensaje=aEnviar.pop();
		mensaje.append("\n");
		try{
			socket->send((char*)mensaje.c_str(),mensaje.size());
		}catch(std::exception& e){
			LOG(ERROR) << e.what();
			socket->shutdown();
		}
		//LOG(INFO)<<"enviado msg: "<<mensaje;
	}
}

/*aniade a la cola de envios data. data debe ser string sin fin de linea*/
void SendThread::enviar(std::string data){
	aEnviar.push(data);
}

/******************************************************************************/
RecvThread::RecvThread(Socket* s, Observer* o):socket(s), observador(o) {}

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
			try{
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
			}catch(std::exception& e){
				LOG(ERROR) << e.what();
				continuar=false;
				socket->shutdown();
			}
		}while(continuar);
		if(recibi){
			std::string recvStr=recibido.str();
			observador->notify(new MessageRecieved(recvStr,socket->descriptor));
		}else{
			usleep(TIMEOUT);
		}
	}
	observador->notify(new ConnectionEnded(socket->descriptor));
}
