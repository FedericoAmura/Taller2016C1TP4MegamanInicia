#include <glog/logging.h>
#include <map>
#include <string>
#include <unistd.h>

#include "Game.h"
#include "Handler.h"
#include "HandlerCoordinator.h"
#include "Model/MyLevel.h"
#include "../common/CommunicationCodes.h"

#define TIMEOUT 10000

/*creates game with server as communications*/
Game::Game(Server* server):
goOn(true),
server(server),
manager(this),
level(nullptr),
firstClient(-1) {
	manager.setHandler(1,new AcceptConnection(this));
	manager.setHandler(2,new RecvMessage(this));
	manager.setHandler(3,new SendMessage(this));
	manager.setHandler(4,new DisconnectClient(this));
	manager.setHandler(5,new FinishLevel(this));
}

Game::~Game() {
	/*join level thread*/
	stopLevel();
	//candidato para extraer, liberar clientes
	std::map<int,Socket*>::iterator it=clients.begin();
	for(; it!=clients.end(); it++){
		delete (it->second);
	}
	/*free event queue resources*/
	while(!eventQueue.empty()){
		delete eventQueue.pop();
	}
}

/*Starts event loop. Finishes when stop() is called*/
void Game::run(){
	//todo initialize certain things here
	LOG(INFO)<<"loop eventos juego iniciado";
	while(isntStopped()){
		Event* e=eventQueue.pop();
		manager.handle(e);
	}
	LOG(INFO)<<"loop eventos juego finalizado";
}

/*sends event to event loop*/
void Game::notify(Event* e){
	eventQueue.push(e);
}

/*stops the event loop*/
void Game::stop(){
	Lock l(goOnMutex);
	goOn=false;
	this->notify(new MessageSent("9",0));
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
	if(clients.size()>=4 || levelChosen()){
		//rechazar
		LOG(INFO)<<"Cliente rechazado";
		delete nuevoCliente;
	}else{
		nuevoCliente->iniciarComunicaciones();
		if(clients.size()==0){
			std::string msjPrimero= "sos el primer jugador";
			this->notify(new MessageSent(msjPrimero,descriptor));
			firstClient=descriptor;
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
			(it->second)->enviar(data);
		}
	}else{
		Lock l(clientsMutex);
		if(clients.find(destino)!=clients.end()){
			(clients[destino])->enviar(data);
		}
	}
}

void Game::removeClient(int descriptor) {
	Lock l(clientsMutex);
	std::map<int,Socket*>::iterator it=clients.find(descriptor);
	if(it!=clients.end()){
		delete it->second;
		clients.erase(it);
		LOG(INFO)<<"cliente desconectado, id:"<<descriptor;
	}
	if(clients.empty())
		stopLevel();
}
/****************************************************/

/*chooses and creates the level selected, if no level is currently running
 * post: level is initialized*/
void Game::selectLevel(int levelId, int client){
	/*TODO default level for now*/
	if((!levelChosen())&&(client==firstClient)){
		LOG(INFO)<<"level seleccionado: "<<levelId;
		std::stringstream msg;
		msg<<START_LEVEL_SCREEN<<" "<<levelId;
		notify(new MessageSent(msg.str(),0));
		level= new MyLevel(this,"../server/Model/simplex.json");
		level->start();
	}
}

/*returns the current level, or null if no level is running*/
MyLevel* Game::getLevel(){
	if(levelChosen())
		return level;
	else
		return nullptr;
}

/*stops,joins, and destroys level.
 * post:level is set to null*/
void Game::stopLevel(){
	//todo send lost,won,exited
	LOG(INFO)<<"cerrando nivel";
	if(levelChosen()){
		if(level->isRunning()){
			level->stop();
			level->join();
		}
		LOG(INFO)<<"destruyendo nivel";
		delete level;
		level=nullptr;
		std::string levelExitMsg="7";
		this->notify(new MessageSent(levelExitMsg,0));
	}
}

/*moves the corresponding player*/
//todo move more than one megaman
void Game::movePlayer(int keyPressed, int source) {
	if(levelChosen()){
		if (KEY_UP == keyPressed) getLevel()->moveMegaman('w');
		if (KEY_RIGHT == keyPressed) getLevel()->moveMegaman('d');
		if (KEY_DOWN == keyPressed) getLevel()->moveMegaman('s');
		if (KEY_LEFT == keyPressed) getLevel()->moveMegaman('a');
	}
}

/*returns true if a level has alredy started*/
bool Game::levelChosen() {
	if(level==nullptr)
		return false;
	else
		return true;
}


