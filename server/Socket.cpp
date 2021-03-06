/*
 * Socket.cpp
 *
 *  Created on: Apr 18, 2016
 *      Author: nicolas
 */

#include "Socket.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdexcept>
#include <glog/logging.h>

/*crea un nuevo socket*/
Socket::Socket(Observer* modelo):modelo(modelo),sendThr(this),
recvThr(this,modelo),comunicandose(false),abierto(true){
	descriptor=socket(AF_INET,SOCK_STREAM,0);
	if(descriptor<0){
		throw std::runtime_error("Error:creacion socket");
	}
}

/*arma el socket a partir de un descriptor*/
Socket::Socket(int descriptor,Observer* modelo):modelo(modelo),
		sendThr(this),recvThr(this,modelo),comunicandose(false),
		abierto(true),descriptor(descriptor){
}

/*apaga y cierra el socket*/
Socket::~Socket(){
	this->shutdown();
	sendThr.enviar("9");//destrabador
	if(comunicandose){
		sendThr.join();
		recvThr.join();
	};
	LOG(INFO)<<"socket cerrado final";
	close(descriptor);
}

/*apaga el socket*/
void Socket::shutdown(){
	if(this->estaAbierto()){
		Lock l(abiertoMutex);
		abierto=false;
		::shutdown(descriptor,SHUT_RDWR);
		LOG(INFO)<<"socket apagado";
	}
}

/*envia hacia socketDescriptor, largo bytes de data
 * devuelve true en exito,si el socket esta cerrado false*
 *advertencia: no controla largos o datos de data*/
bool Socket::send(char* data,int largo){
	int bytesRestantes=largo;
	while(bytesRestantes>0){
		int sent= ::send(descriptor,
				data+(largo-bytesRestantes),
				bytesRestantes,MSG_NOSIGNAL);
		if(sent<0){
			throw std::runtime_error("Error:envio en socket");
		}else if (sent==0){
			return false;
		}else{
			bytesRestantes-=sent;
		}
	}
	return true;
}

/*recive en data, "largo" bytes, desde socket descriptor
 * devuelve true en exito,si el socket esta cerrado false*
 *advertencia: no controla largos o datos de data*/
bool Socket::recieve(char* data,int largo){
	int bytesRestantes=largo;
	while(bytesRestantes>0){
		int recieved= ::recv(descriptor,
				data+(largo-bytesRestantes),
				bytesRestantes,MSG_NOSIGNAL);
		if(recieved<0){
			throw std::runtime_error("Error:recepcion socket");
		}else if (recieved==0){
			return false;
		}else{
			bytesRestantes-=recieved;
		}
	}
	return true;
}

/*pasa el evento al modelo*/
void Socket::notify(Event* e){
	modelo->notify(e);
}

/*aniade mensaje a la cola de envio*/
void Socket::enviar(std::string mensaje){
	sendThr.enviar(mensaje);
}

/*inicia los threads de recepcion y envio*/
void Socket::iniciarComunicaciones(){
	comunicandose=true;
	sendThr.start();
	recvThr.start();
}

/*responde si el socket sigue abierto*/
bool Socket::estaAbierto(){
	Lock l(abiertoMutex);
	bool retorno=abierto;
	return retorno;
}
