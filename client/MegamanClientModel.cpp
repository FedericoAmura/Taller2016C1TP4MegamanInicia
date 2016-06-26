/*
 * MegamanClientModel.cpp
 *
 *  Created on: May 18, 2016
 *      Author: freddy
 */

#include "MegamanClientModel.h"

#include <gdkmm/general.h>
#include <glibmm/main.h>
#include <iostream>
#include <glog/logging.h>
#include <fstream>

#include "../common/CommunicationCodes.h"
#include "../common/MegamanBeginsConstants.h"
#include "../entities.h"
#include "../json/json.h"
#include "WindowNames.h"

#define LVL_DIR "../levels/"
#define BANNER -1
#define BACKGROUND -10

MegamanClientModel::MegamanClientModel() :
	serverProxy(nullptr),
	clientNumber("0"),
	clientsConnected(0),
	clientsDrawed(0),
	recibirServer(false) {
	levelsStatus[MAGNETMAN] = false;
	levelsStatus[SPARKMAN] = false;
	levelsStatus[RINGMAN] = false;
	levelsStatus[FIREMAN] = false;
	levelsStatus[BOMBMAN] = false;
}

MegamanClientModel::~MegamanClientModel() {
	disconnectServer();
}

Drawables& MegamanClientModel::getDrawables() {
	return drawables;
}

void MegamanClientModel::run() {
	try{
		while (recibirServer) {
			std::string message = serverProxy->recibirHasta('\n');
			if (message.length() == 0) continue;
			DLOG(INFO)<<"Mensaje recibido: "<< message;	//DEBUG
			std::stringstream ss(message);
			int commandString; ss >> commandString;

			switch (commandString) {
			case HELLO:
				{
				ss >> clientNumber;
				gameStatusChangeSignal.emit();
				}
				break;
			case CLIENTS_CONNECTED:
				{
				ss >> clientsConnected;
				gameStatusChangeSignal.emit();
				}
				break;
			case DRAW:
				{
				int idDrawable; ss >> idDrawable;
				int idDrawing; ss >> idDrawing;
				int flipped; ss >> flipped;
				double xDrawable; ss >> xDrawable;
				double yDrawable; ss >> yDrawable;
				Drawable* drawable = drawables.getDrawable(idDrawable);
				if (drawable == nullptr) {
					if (idDrawing<9000 || idDrawing>=10000) drawable = new Drawable();
					else {
						drawable = new Drawable(100*clientsDrawed);
						clientsDrawed++;
					}
				}
				drawable->setImage(idDrawing, sprites,flipped);
				drawable->setCoordinates(xDrawable,yDrawable);
				drawables.setDrawable(idDrawable,drawable);
				}
				break;
			case REDRAW:
				{
				int idDrawable; ss >> idDrawable;
				int idDrawing; ss >> idDrawing;
				int flipped; ss >> flipped;
				Drawable* drawable = drawables.getDrawable(idDrawable);
				if (drawable == nullptr) continue;
				drawable->setImage(idDrawing,sprites,flipped);
				drawable->setChanged(true);
				}
				break;
			case MOVE:
				{
				int idDrawable; ss >> idDrawable;
				double xDrawable; ss >> xDrawable;
				double yDrawable; ss >> yDrawable;
				Drawable* drawable = drawables.getDrawable(idDrawable);
				if (drawable == nullptr) continue;
				int idDrawing = drawable->getSpriteId();
				//Desplazo el drawable a uno de movimiento que empiece el ciclo
				if (idDrawing>=MEGAMAN_IDLE_0 && idDrawing<=MEGAMAN_IDLE_2) drawable->setImage(MEGAMAN_RUN_0,sprites,drawable->getFlipped());
				else if (idDrawing==FIREMAN_IDLE_0) drawable->setImage(FIREMAN_RUN_0,sprites,drawable->getFlipped());
				else if (idDrawing==RINGMAN_IDLE) drawable->setImage(RINGMAN_RUN_0,sprites,drawable->getFlipped());
				else if (idDrawing==MAGNETMAN_IDLE) drawable->setImage(MAGNETMAN_ATTACK,sprites,drawable->getFlipped());
				else if (idDrawing==BOMBMAN_IDLE) drawable->setImage(BOMBMAN_JUMP_FRONT,sprites,drawable->getFlipped());
				else if (idDrawing==SPARKMAN_IDLE) drawable->setImage(SPARKMAN_CAST_ATTACK_2,sprites,drawable->getFlipped());
				drawable->setCoordinates(xDrawable,yDrawable);
				drawable->setChanged(true);
				}
				break;
			case KILL:
				{
				int idDrawable; ss >> idDrawable;
				drawables.removeDrawable(idDrawable);
				}
				break;
			case SOUND:
				{
				std::string idSound; ss >> idSound;
				std::cout << "Tendria que reproducir el sonido " << idSound << std::endl;
				}
				break;
			case START_LEVEL_SCREEN:
				{
				clientsDrawed = 0;
				int idLevel; ss >> idLevel;
				Json::Value level_json;
				std::string filename = LVL_DIR;
				if (idLevel==MAGNETMAN) filename.append("magnetman.json");
				else if (idLevel==SPARKMAN) filename.append("sparkman.json");
				else if (idLevel==RINGMAN) filename.append("ringman.json");
				else if (idLevel==FIREMAN) filename.append("fireman.json");
				else if (idLevel==BOMBMAN) filename.append("bombman.json");
				std::ifstream configFile(filename);
				configFile >> level_json;
				std::string background = level_json["background"].asString();
				//Seteo fondo
				Drawable* drawable = drawables.getDrawable(BACKGROUND);
				if (drawable == nullptr) drawable = new Drawable();
				else drawable->setChanged(true);
				drawable->setImage(CITY,sprites,false);	//Generico, despues lo cambiamos por el posta
				int tileSize = (double)Gdk::screen_height()/(double)TILES_VERTICAL;
				drawable->getImage().setImage(level_json["background"].asString(),tileSize*TILES_HORIZONTAL,tileSize*TILES_VERTICAL,false);
				drawable->setCoordinates(0,0);
				drawables.setDrawable(BACKGROUND,drawable);
				//Muestro el "GO"
				drawable = drawables.getDrawable(BANNER);
				if (drawable == nullptr) drawable = new Drawable();
				else drawable->setChanged(true);
				drawable->setImage(GO,sprites,false);
				drawable->setCoordinates(10.5,5);
				drawables.setDrawable(BANNER,drawable);
				windowChangeSignal.emit(LEVEL_SCREEN_NAME);
				//Lo saco en un segundo
				Glib::signal_timeout().connect(sigc::bind<int>(sigc::mem_fun(drawables,&Drawables::removeDrawable),BANNER),1000);
				//Empiezo a ciclar los drawables que sea posible
				cicleDrawablesConn = Glib::signal_timeout().connect(sigc::mem_fun(*this,&MegamanClientModel::cicleDrawables),500);
				}
				break;
			case BACK_TO_LEVEL_SELECTION:
				{
				gameStatusChangeSignal.emit();
				//Muestro el "LEVEL OVER"
				Drawable* drawable = drawables.getDrawable(BANNER);
				if (drawable == nullptr) drawable = new Drawable();
				else drawable->setChanged(true);
				drawable->setImage(LEVEL_OVER,sprites,false);
				drawable->setCoordinates(7.5,5);
				drawables.setDrawable(BANNER,drawable);
				//Dejo de ciclar los drawables
				cicleDrawablesConn.disconnect();
				//Lo saco en un segundo
				Glib::signal_timeout().connect(sigc::bind<int>(sigc::mem_fun(drawables,&Drawables::removeDrawable),BANNER),1000);
				//Hago el cambio de pantalla en un segundo
				Glib::signal_timeout().connect(sigc::mem_fun(*this,&MegamanClientModel::backToLevelSelectionSignal),1000);
				}
				break;
			case LIFE_STATUS:
				{
				int player; ss >> player;
				int health; ss >> health;
				int id = HEALTH_BAR;
				if (!player) id++;
				Drawable* drawable = drawables.getDrawable(id);
				if (drawable == nullptr) drawable = new Drawable();
				else drawable->setChanged(true);
				drawable->setImage(HEALTH_BAR,sprites,false);
				if (player) drawable->setCoordinates(1,2);
				else drawable->setCoordinates(TILES_HORIZONTAL-1.5,2);
				drawable->setPercent(health);
				drawables.setDrawable(id,drawable);
				}
				break;
			case LEVEL_STATUS:
				{
				int idLevel; ss >> idLevel;
				bool levelStatus; ss >> levelStatus;
				levelsStatus[idLevel] = levelStatus;
				}
				break;
			case SERVER_DISCONNECTED:
				disconnectServer();
				windowChangeSignal.emit(CONNECTION_SCREEN_NAME);
				break;
			default:
				{
				std::string error = "No se entendio el mensaje: ";
				std::cout << error << message << std::endl;
				serverProxy->enviar(error + message);
				}
				break;
			}
		}
	} catch (...) {
		windowChangeSignal.emit(CONNECTION_SCREEN_NAME);
		DLOG(INFO)<<"Exception";	//DEBUG
	}
}

Signal MegamanClientModel::changeGameStatusSignal() {
	return gameStatusChangeSignal;
}

StringSignal MegamanClientModel::changeScreenSignal() {
	return windowChangeSignal;
}

void MegamanClientModel::connectServer(std::string ip, std::string port) {
	serverProxy = new Socket(ip, port);
	recibirServer = true;
	this->start();
	levelsStatus[MAGNETMAN] = false;
	levelsStatus[SPARKMAN] = false;
	levelsStatus[RINGMAN] = false;
	levelsStatus[FIREMAN] = false;
	levelsStatus[BOMBMAN] = false;
}

std::string MegamanClientModel::getClientNumber() {
	return clientNumber;
}

int MegamanClientModel::getClientsConnected() {
	return clientsConnected;
}

bool MegamanClientModel::getLevelStatus(int idLevel) {
	return levelsStatus[idLevel];
}

void MegamanClientModel::disconnectServer() {
	if (serverProxy!=nullptr) {
		//Dejo de recibir del server y me desconecto de el
		recibirServer = false;
		serverProxy->enviar(CLIENT_DISCONNECTED);serverProxy->enviar("\n");
		//this->join();
		serverProxy->cerrar();
		delete(serverProxy);
		serverProxy = nullptr;
		clientNumber = "0";
	}
}

bool MegamanClientModel::cicleDrawables() {
	//Recorro los drawables y redibujo al siguiente de la secuencia de haberlo
	DrawablesIterator iter = drawables.drawablesIterator();
	for (int i = 0; i < drawables.size(); ++i) {
		Drawable* drawable = (*iter).second;
		if (drawable != nullptr) {
			int spriteID = drawable->getSpriteId();
			bool cicled = false;
			bool flipped = drawable->getFlipped();
			//Cambio el sprite por el siguiente
			switch (spriteID) {
			//Megaman
			case MEGAMAN_IDLE_0:
				spriteID = MEGAMAN_IDLE_1;
				cicled = true;
				break;
			case MEGAMAN_IDLE_1:
				spriteID = MEGAMAN_IDLE_2;
				cicled = true;
				break;
			case MEGAMAN_IDLE_2:
				spriteID = MEGAMAN_IDLE_0;
				cicled = true;
				break;
			case MEGAMAN_RUN_0:
				spriteID = MEGAMAN_RUN_1;
				cicled = true;
				break;
			case MEGAMAN_RUN_1:
				spriteID = MEGAMAN_RUN_2;
				cicled = true;
				break;
			case MEGAMAN_RUN_2:
				spriteID = MEGAMAN_IDLE_0;
				cicled = true;
				break;
			case MEGAMAN_CLIMB:
				flipped = !flipped;
				cicled = true;
				break;
			//Bumby
			case BUMBY_0:
				spriteID = BUMBY_1;
				cicled = true;
				break;
			case BUMBY_1:
				spriteID = BUMBY_0;
				cicled = true;
				break;
			//Met
			case MET_VULNERABLE:
				spriteID = MET_HIDDEN;
				cicled = true;
				break;
			case MET_HIDDEN:
				spriteID = MET_VULNERABLE;
				cicled = true;
				break;
			//Sniper
			case SNIPER_ATTACK:
				spriteID = SNIPER_VULNERABLE;
				cicled = true;
				break;
			case SNIPER_VULNERABLE:
				spriteID = SNIPER_ATTACK;
				cicled = true;
				break;
			case SNIPER_JUMP:
				spriteID = SNIPER_DEFEND;
				cicled = true;
				break;
			case SNIPER_DEFEND:
				spriteID = SNIPER_JUMP;
				cicled = true;
				break;
			//Fireman
			case FIREMAN_RUN_0:
				spriteID = FIREMAN_RUN_1;
				cicled = true;
				break;
			case FIREMAN_RUN_1:
				spriteID = FIREMAN_RUN_2;
				cicled = true;
				break;
			case FIREMAN_RUN_2:
				spriteID = FIREMAN_RUN_3;
				cicled = true;
				break;
			case FIREMAN_RUN_3:
				spriteID = FIREMAN_IDLE_0;
				cicled = true;
				break;
			case FIREMAN_IDLE_0:
				spriteID = FIREMAN_IDLE_1;
				cicled = true;
				break;
			case FIREMAN_IDLE_1:
				spriteID = FIREMAN_IDLE_0;
				cicled = true;
				break;
			//Ringman
			case RINGMAN_RUN_0:
				spriteID = RINGMAN_RUN_1;
				cicled = true;
				break;
			case RINGMAN_RUN_1:
				spriteID = RINGMAN_RUN_2;
				cicled = true;
				break;
			case RINGMAN_RUN_2:
				spriteID = RINGMAN_RUN_3;
				cicled = true;
				break;
			case RINGMAN_RUN_3:
				spriteID = RINGMAN_IDLE;
				cicled = true;
				break;
			//Ringman
			case MAGNETMAN_ATTACK:
				spriteID = MAGNETMAN_IDLE;
				cicled = true;
				break;
			//Bombman
			case BOMBMAN_JUMP_FRONT:
				spriteID = BOMBMAN_IDLE;
				cicled = true;
				break;
			case BOMBMAN_IDLE:
				spriteID = BOMBMAN_JUGGLE;
				cicled = true;
				break;
			case BOMBMAN_JUGGLE:
				spriteID = BOMBMAN_IDLE;
				cicled = true;
				break;
			//Sparkman
			case SPARKMAN_CAST_ATTACK_2:
				spriteID = SPARKMAN_IDLE;
				cicled = true;
				break;
			case SPARKMAN_IDLE:
				spriteID = SPARKMAN_PREPARE_0_ATTACK_1;
				cicled = true;
				break;
			case SPARKMAN_PREPARE_0_ATTACK_1:
				spriteID = SPARKMAN_CAST_ATTACK_1;
				cicled = true;
				break;
			case SPARKMAN_CAST_ATTACK_1:
				spriteID = SPARKMAN_PREPARE_1_ATTACK_1;
				cicled = true;
				break;
			case SPARKMAN_PREPARE_1_ATTACK_1:
				spriteID = SPARKMAN_IDLE;
				cicled = true;
				break;
			default:
				break;
			}
			if (cicled) {
				drawable->setImage(spriteID,sprites,flipped);
				drawable->setChanged(true);
			}
		}
		++iter;
	}
	return true;
}

void MegamanClientModel::serverSendLevelSelected(int levelCode) {
	if (serverProxy!=nullptr) {
		std::string mensaje;
		mensaje.append(std::to_string(SELECT_LEVEL));
		mensaje.append(" ");
		mensaje.append(std::to_string(levelCode));
		mensaje.append("\n");
		serverProxy->enviar(mensaje);
	}
}

void MegamanClientModel::serverSendKeyboard(int keyCode) {
	if (serverProxy!=nullptr) {
		std::string mensaje = std::to_string(KEYBOARD_STATE);
		mensaje.append(" ");
		mensaje.append(std::to_string(keyCode));
		mensaje.append("\n");
		serverProxy->enviar(mensaje);
	}
}

bool MegamanClientModel::backToLevelSelectionSignal() {
	windowChangeSignal.emit(LEVEL_SELECTOR_SCREEN_NAME);
	return false;
}

