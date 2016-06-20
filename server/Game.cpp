#include <glog/logging.h>
#include <map>
#include <string>
#include <sstream>
#include <unistd.h>
#include <dirent.h>
#include <fstream>
#include <iostream>

#include "Game.h"
#include "Handler.h"
#include "HandlerCoordinator.h"
#include "Model/MyLevel.h"
#include "../common/CommunicationCodes.h"
#include "../common/MegamanBeginsConstants.h"
#include "Metadata.h"

#define TIMEOUT 10000
#define NUMBER_OF_LEVELS 5
#define LVL_DIR "../levels/"
#define MAX_CLIENTS 4

/*creates game with server as communications*/
Game::Game(Server* server)
:goOn(true),
 server(server),
 manager(this),
 level(nullptr),
 metadata(this),
 firstClient(-1){
	manager.setHandler(1,new AcceptConnection(this));
	manager.setHandler(2,new RecvMessage(this));
	manager.setHandler(3,new SendMessage(this));
	manager.setHandler(4,new DisconnectClient(this));
	manager.setHandler(5,new FinishLevel(this));
	for(int i =1; i<=MAX_CLIENTS; i++){
		availableClientNumbers.push(i);
	}
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
	DLOG(INFO)<<"loop eventos juego iniciado";
	while(isntStopped()){
		Event* e=eventQueue.pop();
		manager.handle(e);
		delete e;
	}
	DLOG(INFO)<<"loop eventos juego finalizado";
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

/***************************************************/
/*adds client to game, max 4 clients*/
void Game::addClient(int descriptor){
	Socket* nuevoCliente= new Socket(descriptor,this);
	Lock l(clientsMutex);
	if (availableClientNumbers.empty() || levelChosen()) {
		//rechazar
		LOG(INFO)<<"Cliente rechazado";
		std::stringstream mensajeChau;
		mensajeChau<<SERVER_DISCONNECTED;
		nuevoCliente->enviar(mensajeChau.str());
		delete nuevoCliente;
	}else{
		int clientNumber = availableClientNumbers.front();
		availableClientNumbers.pop();

		nuevoCliente->iniciarComunicaciones();

		if(clients.size()==0){
			firstClient=descriptor;
		}
		clients[descriptor]=nuevoCliente;

		std::stringstream mensajeNumeroClient;
		mensajeNumeroClient<<HELLO<<" "<<clientNumber ;
		this->notify(new MessageSent(mensajeNumeroClient.str(),descriptor));

		std::stringstream mensajeCantConectados;
		mensajeCantConectados<<CLIENTS_CONNECTED<<" "<<clients.size() ;
		this->notify(new MessageSent(mensajeCantConectados.str(),0));

		clientNum[descriptor]=clientNumber ;
		metadata.addClient(descriptor,clientNum[descriptor]);
		LOG(INFO)<<"Cliente conectado nro: "
				<<clientNumber<<" descriptor: "<<descriptor;
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
	if(levelChosen())
		level->removeClient(clientNum[descriptor]);

	Lock l(clientsMutex);
	std::map<int,Socket*>::iterator it=clients.find(descriptor);
	if(it!=clients.end()){
		delete it->second;
		clients.erase(it);
		LOG(INFO)<<"cliente "<<clientNum[descriptor]<<" desconectado, id:"<<descriptor;
	}

	metadata.removeClient(descriptor);
	availableClientNumbers.push(clientNum[descriptor]);
	clientNum.erase(descriptor);

	if(clients.empty()){
		stopLevel();
	}else{
		if(descriptor==firstClient){
			firstClient=metadata.getClient(1)->getDescriptor();
			std::stringstream mensajeNumeroClient;
			mensajeNumeroClient<<HELLO<<" 1";
			this->notify(new MessageSent(mensajeNumeroClient.str(),firstClient));
		}
		std::stringstream mensajeCantConectados;
		mensajeCantConectados<<CLIENTS_CONNECTED<<" "<<clients.size() ;
		this->notify(new MessageSent(mensajeCantConectados.str(),0));
	}
}
/****************************************************/

/*chooses and creates the level selected, if no level is currently running
 * post: level is initialized*/
void Game::selectLevel(int levelId, int client){
	if((!levelChosen())&&(client==firstClient)){
		LOG(INFO)<<"level seleccionado: "<<levelId;
		std::string levelFilePath;
		levelFilePath = LVL_DIR + getLevelFiles()[levelId];
		try{
			MyLevel* lvl=new MyLevel(this,levelFilePath,&metadata,levelId);
			level= lvl;//to avoid asigning invalid in case of error
			level->start();
			std::stringstream msg;
			msg<<START_LEVEL_SCREEN<<" "<<levelId;
			notify(new MessageSent(msg.str(),0));
		}catch(std::exception& e){
			LOG(ERROR)<<e.what();
			level=nullptr;
		}
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
	if(levelChosen()){
		if(level->isRunning()){
			DLOG(INFO)<<"cerrando nivel";
			level->stop();
			level->join();
		}
		DLOG(INFO)<<"destruyendo nivel";
		delete level;
		level=nullptr;
		std::string levelExitMsg="7";
		this->notify(new MessageSent(levelExitMsg,0));
	}
}

/*moves the corresponding player*/
void Game::movePlayer(uint keyState, int source) {
	if(levelChosen()){
		getLevel()->changeKeyState(keyState,clientNum[source]);
	}
}

/*returns true if a level has alredy started*/
bool Game::levelChosen() {
	if(level==nullptr)
		return false;
	else
		return true;
}

void Game::resetClientLives() {
	int numOfClients=this->metadata.getNumberOfClients();
	for(int i=1; i<=numOfClients; i++){
		ClientData* client=metadata.getClient(i);
		if(client){
			client->getLives().inc(1);
			client->getLives().inc(1);
			client->getLives().inc(1);
		}
	}
}

std::vector<std::string> Game::findFilesInDir() {
	std::vector<std::string> files;
	system("ls ../levels/ > available_levels");
	std::ifstream f;
	std::string line;
	f.open ("available_levels");
	uint count = 0;
	if (f.is_open()) {
		while(getline (f, line)) {
			if (line.find(".json") == std::string::npos) continue;
			++count;
			files.push_back(line);
		}
		f.close();
	}
	if (count != NUMBER_OF_LEVELS) {
		throw std::runtime_error(
				"There must be exactly five valid level files"
				" in the levels folder.");
	}
	return files;
}

std::map<uint, std::string> Game::getLevelFiles() {
	std::vector<std::string> files = findFilesInDir();
	std::map<uint, std::string> levelFiles;
	for (uint i = 0; i != files.size(); ++i){
		//Open File
		std::string filename = LVL_DIR + files[i];
		std::ifstream in(filename);
		Json::Value level_json;
		in >> level_json;
		bool valid = level_json["valid"].asBool();
		if (!valid) {
			throw std::runtime_error(
					"Level file " + filename + " is not valid.");
		} else {
			std::string boss = level_json["Boss"].asString();
			if (boss == "Bombman"){
				levelFiles[BOMBMAN] = filename;
			} else if (boss == "Magnetman"){
				levelFiles[MAGNETMAN] = filename;
			} else if (boss == "Sparkman"){
				levelFiles[SPARKMAN] = filename;
			} else if (boss == "Ringman"){
				levelFiles[RINGMAN] = filename;
			} else if (boss == "Fireman"){
				levelFiles[FIREMAN] = filename;
			} else {
				throw std::runtime_error("Invalid level file "
						+ files[i]
								+ " marked as valid.");
			}
		}
		in.close();
	}
	return levelFiles;
}
