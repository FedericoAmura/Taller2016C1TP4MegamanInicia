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

#include "../common/CommunicationCodes.h"
#include "../common/MegamanBeginsConstants.h"
#include "../entities.h"
#include "WindowNames.h"

MegamanClientModel::MegamanClientModel() :
	serverProxy(nullptr),
	clientNumber("0"),
	clientsConnected(0),
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
		//std::cout << message << std::endl;	//DEBUG
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
				drawable = new Drawable();
			}
			uint id = (uint)idDrawing;
			drawable->setImage(id, sprites.get(id),sprites.getWidth(id),sprites.getHeight(id),flipped);
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
			uint id = (uint)idDrawing;
			drawable->setImage(id,sprites.get(id),sprites.getWidth(id),sprites.getHeight(id),flipped);
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
			int idLevel; ss >> idLevel;
			idLevel += 6000;
			//Seteo fondo
			Drawable* drawable = drawables.getDrawable(idLevel);
			if (drawable == nullptr) {
				drawable = new Drawable();
			}
			drawable->setImage(idLevel,sprites.get(idLevel),sprites.getWidth(idLevel),sprites.getHeight(idLevel),false);
			drawable->setCoordinates(0,0);
			drawables.setDrawable(idLevel,drawable);
			//Muestro el "GO"
			drawable = drawables.getDrawable(GO);
			if (drawable == nullptr) {
				drawable = new Drawable();
			}
			drawable->setImage(GO,sprites.get(GO),sprites.getWidth(GO),sprites.getHeight(GO),false);
			drawable->setCoordinates(10.5,5);
			drawables.setDrawable(GO,drawable);
			windowChangeSignal.emit(LEVEL_SCREEN_NAME);
			//Lo saco en un segundo
			Glib::signal_timeout().connect(sigc::bind<int>(sigc::mem_fun(drawables,&Drawables::removeDrawable),GO),1000);
			}
			break;
		case BACK_TO_LEVEL_SELECTION:
			{
			gameStatusChangeSignal.emit();
			//Muestro el "LEVEL OVER"
			Drawable* drawable = drawables.getDrawable(LEVEL_OVER);
			if (drawable == nullptr) {
				drawable = new Drawable();
			}
			drawable->setImage(LEVEL_OVER,sprites.get(LEVEL_OVER),sprites.getWidth(LEVEL_OVER),sprites.getHeight(LEVEL_OVER),false);
			drawable->setCoordinates(7.5,5);
			drawables.setDrawable(LEVEL_OVER,drawable);
			//Lo saco en un segundo
			Glib::signal_timeout().connect(sigc::bind<int>(sigc::mem_fun(drawables,&Drawables::removeDrawable),LEVEL_OVER),1000);
			//Hago el cambio de pantalla en un segundo
			Glib::signal_timeout().connect(sigc::mem_fun(*this,&MegamanClientModel::backToLevelSelectionSignal),1000);
			}
			break;
		case LIFE_STATUS:
			{
			int player; ss >> player;
			int health; ss >> health;
			Drawable* drawable = drawables.getDrawable(HEALTH_BAR);
			if (drawable == nullptr) {
				drawable = new Drawable();
			}
			drawable->setImage(HEALTH_BAR,sprites.get(HEALTH_BAR),sprites.getWidth(HEALTH_BAR),sprites.getHeight(HEALTH_BAR),false);
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

