/*
 * server_Juego1.cpp
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */



#include "Juego.h"

#include <glog/logging.h>
#include <map>
#include <string>
#include <unistd.h>
#include "Handler.h"
#include "HandlerCoordinator.h"
#include "Model/MyLevel.h"

#define TIMEOUT 10000

Juego::Juego(Server* server):continuar(true),server(server),
manager(this),level(this) {
	manager.setHandler(1,new AceptarConeccion(this));
	manager.setHandler(2,new RecibirMensaje(this));
	manager.setHandler(3,new EnviarMensaje(this));
	level.start();
}

Juego::~Juego() {
	/*join level thread*/
	if(level.isRunning()){
		level.stop();
		level.join();
	}

	/*free event queue resources*/
	while(!eventQueue.empty()){
		delete eventQueue.front();
		eventQueue.pop();
	}

	//candidato para extraer, liberar clientes
	std::map<int,Socket*>::iterator it=clientes.begin();
	for(; it!=clientes.end(); it++){
		delete (it->second);
	}
}

/*inicia el ciclo de manejo de eventos.
 * Finaliza al pedirle al juego que se cierre, por medio de un evento mas*/
void Juego::run(){
	//todo lanzar evento inicializar juego
	LOG(INFO)<<"loop eventos juego iniciado";
	while(seguirCorriendo()){
		//todo lock .empty, o funcion
		if(eventQueue.empty()){
			usleep(TIMEOUT);
		}else{
			Evento* e;
			{
				Lock l(queueMutex);
				e=eventQueue.front();
				eventQueue.pop();
			}
			manager.handle(e);
		}
	}
	LOG(INFO)<<"loop eventos juego finalizado";
}

/*aniade el evento a la cola de eventos*/
void Juego::notificar(Evento* e){
	Lock l(queueMutex);
	eventQueue.push(e);
}

/*inicia el cierre del juego*/
void Juego::cerrar(){
	Lock l(continuarMutex);
	continuar=false;
}

/*devuelve true si el juego no debe cerrarse*/
bool Juego::seguirCorriendo(){
	Lock l(continuarMutex);
	return continuar;
}

/**********a potencialmente extrar clase************/
/*aniade el cliente al juego, o lo rechaza si ya hay 4*/
void Juego::aniadirCliente(int descriptor){
	Socket* nuevoCliente= new Socket(descriptor,this);
	Lock l(clientesMutex);
	if(clientes.size()>=4){
		//rechazar
		LOG(INFO)<<"Cliente rechazado";
		delete nuevoCliente;
	}else{
		//todo 1era coneccion especial
		nuevoCliente->iniciarComunicaciones();
		clientes[descriptor]=nuevoCliente;
		LOG(INFO)<<"Cliente conectado nro: "
				<<clientes.size()<<" descriptor: "<<descriptor;
	}
}

/*envia data al cliente destino. si destino 0 lo envia a todos*/
void Juego::enviarA(std::string data, int destino){
	if(destino==0){
		Lock l(clientesMutex);
		std::map<int,Socket*>::iterator it=clientes.begin();
		for(; it!=clientes.end(); it++){
			(it->second)->enviar((char*)data.c_str());
		}
	}else{
		Lock l(clientesMutex);
		if(clientes.find(destino)!=clientes.end()){
			(clientes[destino])->enviar((char*)data.c_str());
		}
	}
}

MyLevel* Juego::getLevel(){
	return &level;
}
