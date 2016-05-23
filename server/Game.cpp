#include <glog/logging.h>
#include <map>
#include <string>
#include <unistd.h>

#include "Game.h"
#include "Handler.h"
#include "HandlerCoordinator.h"
#include "Model/MyLevel.h"

#define TIMEOUT 10000

/*creates game with server as communications*/
Game::Game(Server* server):goOn(true),server(server),
manager(this),level(nullptr),firstClient(0) {
	manager.setHandler(1,new AceptarConeccion(this));
	manager.setHandler(2,new RecibirMensaje(this));
	manager.setHandler(3,new EnviarMensaje(this));
	//todo select level from client
	this->selectLevel(1234);
}

Game::~Game() {
	/*join level thread*/
	stopLevel();

	/*free event queue resources*/
	while(!eventQueue.empty()){
		delete eventQueue.front();
		eventQueue.pop();
	}

	//candidato para extraer, liberar clientes
	std::map<int,Socket*>::iterator it=clients.begin();
	for(; it!=clients.end(); it++){
		delete (it->second);
	}
}

/*Starts event loop. Finishes when stop() is called*/
void Game::run(){
	//todo initialize certain things here
	LOG(INFO)<<"loop eventos juego iniciado";
	while(isntStopped()){
		bool empty;
		{
			Lock l(queueMutex);
			empty=eventQueue.empty();
		}
		if(empty){
			usleep(TIMEOUT);
		}else{
			Event* e;
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

/*sends event to event loop*/
void Game::notify(Event* e){
	Lock l(queueMutex);
	eventQueue.push(e);
}

/*stops the event loop*/
void Game::stop(){
	Lock l(goOnMutex);
	goOn=false;
}

/*returns true if game should keep running*/
bool Game::isntStopped(){
	Lock l(goOnMutex);
	return goOn;
}

/**********a potencialmente extrar clase************/
/*adds client to game, max 4 clients*/
void Game::addClient(int descriptor){
	Socket* nuevoCliente= new Socket(descriptor,this);
	Lock l(clientsMutex);
	if(clients.size()>=4){
		//rechazar
		LOG(INFO)<<"Cliente rechazado";
		delete nuevoCliente;
	}else{
		//todo 1era coneccion especial
		nuevoCliente->iniciarComunicaciones();
		if(clients.size()==0){
			std::string msjPrimero= "sos el primer jugador";
			this->notify(new MessageSent(msjPrimero,descriptor));
		}
		clients[descriptor]=nuevoCliente;
		LOG(INFO)<<"Cliente conectado nro: "
				<<clients.size()<<" descriptor: "<<descriptor;
	}
}

/*sends data to destination. if destination is 0 then to all clients*/
void Game::sendTo(std::string data, int destino){
	if(destino==0){
		Lock l(clientsMutex);
		std::map<int,Socket*>::iterator it=clients.begin();
		for(; it!=clients.end(); it++){
			(it->second)->enviar((char*)data.c_str());
		}
	}else{
		Lock l(clientsMutex);
		if(clients.find(destino)!=clients.end()){
			(clients[destino])->enviar((char*)data.c_str());
		}
	}
}

/****************************************************/

/*chooses and creates the level selected, if no level is currently running
 * post: level is initialized*/
void Game::selectLevel(int levelId){
	/*TODO default level for now*/
	if(level==nullptr){
		level= new MyLevel(this);
		LOG(INFO)<<"level seleccionado: "<<levelId;
		level->start();
	}
}

/*returns the current level, or null if no level is running*/
MyLevel* Game::getLevel(){
	if(level!=nullptr)
		return level;
	else
		return nullptr;
}

/*stops,joins, and destroys level.
 * post:level is set to null*/
void Game::stopLevel(){
	if(level->isRunning()){
		level->stop();
		level->join();
	}
	delete level;
	level=nullptr;
	std::string levelExitMsg="6 (back to level selection pls)";
	this->notify(new MessageSent(levelExitMsg,0));
}
