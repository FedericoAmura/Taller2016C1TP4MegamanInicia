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

#include "../common/CommunicationCodes.h"
#include "../common/MegamanBeginsConstants.h"
#include "../entities.h"
#include "WindowNames.h"

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
			idLevel += 6000;
			//Seteo fondo
			Drawable* drawable = drawables.getDrawable(BACKGROUND);
			if (drawable == nullptr) {
				drawable = new Drawable();
			}
			drawable->setImage(idLevel,sprites,false);
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
			cicleDrawablesConn = Glib::signal_timeout().connect(sigc::mem_fun(*this,&MegamanClientModel::cicleDrawables),300);
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
			Drawable* drawable = drawables.getDrawable(HEALTH_BAR);
			if (drawable == nullptr) drawable = new Drawable();
			else drawable->setChanged(true);
			drawable->setImage(HEALTH_BAR,sprites,false);
			if (player) drawable->setCoordinates(1,2);
			else drawable->setCoordinates(TILES_HORIZONTAL-1,2);
			drawable->setPercent(health);
			drawables.setDrawable(HEALTH_BAR,drawable);
			}
			break;
		case LEVEL_STATUS:
			{
			int idLevel; ss >> idLevel;
			bool levelStatus; ss >> levelStatus;
			levelsStatus[idLevel] = levelStatus;
			}
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
			case MEGAMAN_CLIMB:
				flipped = !flipped;
				cicled = true;
				break;
			case BUMBY_0:
				spriteID = BUMBY_1;
				cicled = true;
				break;
			case BUMBY_1:
				spriteID = BUMBY_0;
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

