/*
 * MegamanClientModel.cpp
 *
 *  Created on: May 18, 2016
 *      Author: freddy
 */

#include "MegamanClientModel.h"

#include <cstdlib>
#include <iostream>

#include "WindowNames.h"
#include "../common/MegamanBeginsConstants.h"
#include "../common/CommunicationCodes.h"

MegamanClientModel::MegamanClientModel() :
	serverProxy(nullptr),
	clientNumber("0"),
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
			Drawable* drawable = drawables.getDrawable(idDrawable);
			if (drawable == nullptr) continue;
			//TODO Por ahora lo dibujamos arafue
			drawable->setCoordinates(TILES_HORIZONTAL,TILES_VERTICAL);
			drawable->setChanged(true);
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
			/*idLevel += 6000;
			Drawable* drawable = new Drawable();
			drawable->setImage(7000,sprites.get(idLevel),sprites.getWidth(idLevel),sprites.getHeight(idLevel),false);
			drawable->setCoordinates(0,0);
			drawables.setDrawable(7000,drawable);*/

			backgroundChangeSignal.emit("");
			windowChangeSignal.emit(LEVEL_SCREEN_NAME);
			}
			break;
		case BACK_TO_LEVEL_SELECTION:
			gameStatusChangeSignal.emit();
			windowChangeSignal.emit(LEVEL_SELECTOR_SCREEN_NAME);
			break;
		case LIFE_STATUS:
			{
			int player; ss >> player;
			int health; ss >> health;
			Drawable* drawable = drawables.getDrawable(8000);
			if (drawable == nullptr) {
				drawable = new Drawable();
			}
			drawable->setImage(8000,sprites.get(8000),sprites.getWidth(8000),sprites.getHeight(8000),false);
			if (player) drawable->setCoordinates(1,2);
			else drawable->setCoordinates(TILES_HORIZONTAL-1,2);
			drawable->setPercent(health);
			drawables.setDrawable(8000,drawable);
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

DoubleIntSignal MegamanClientModel::changeHealthSignal() {
	return healthChangeSignal;
}

StringSignal MegamanClientModel::changeScreenSignal() {
	return windowChangeSignal;
}

StringSignal MegamanClientModel::changeBackgroundSignal() {
	return backgroundChangeSignal;
}

void MegamanClientModel::connectServer(std::string ip, std::string port) {
	serverProxy = new Socket(ip, port);
	recibirServer = true;
	this->start();
}

std::string MegamanClientModel::getClientNumer() {
	return clientNumber;
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

