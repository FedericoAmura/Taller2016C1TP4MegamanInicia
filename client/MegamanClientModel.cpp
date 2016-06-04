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
serverProxy(nullptr) {
	recibirServer = false;
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
		std::string commandString;
		ss >> commandString;
		int command = atoi(commandString.c_str());

		switch (command) {
		case DRAW:
			{
			std::string idDrawable; ss >> idDrawable;
			std::string idDrawing; ss >> idDrawing;
			std::string flipped; ss >> flipped;
			double xDrawable; ss >> xDrawable;
			double yDrawable; ss >> yDrawable;
			Drawable* drawable = drawables.getDrawable(atoi(idDrawable.c_str()));
			if (drawable == 0) {
				drawable = new Drawable();
				drawable->setIsDrawed(false);
			}
			uint id = (uint)atoi(idDrawing.c_str());
			drawable->setImage(sprites.get(id),sprites.getWidth(id),sprites.getHeight(id),atoi(flipped.c_str()));
			drawable->setCoordinates(xDrawable,yDrawable);
			drawable->setDraw(true);
			drawables.setDrawable(atoi(idDrawable.c_str()),drawable);
			}
			break;
		case REDRAW:
			{
			std::string idDrawable; ss >> idDrawable;
			std::string idDrawing; ss >> idDrawing;
			std::string flipped; ss >> flipped;
			Drawable* drawable = drawables.getDrawable(atoi(idDrawable.c_str()));
			uint id = (uint)atoi(idDrawing.c_str());
			drawable->setImage(sprites.get(id),sprites.getWidth(id),sprites.getHeight(id),atoi(flipped.c_str()));
			drawable->setDraw(true);
			}
			break;
		case MOVE:
			{
			std::string idDrawable; ss >> idDrawable;
			double xDrawable; ss >> xDrawable;
			double yDrawable; ss >> yDrawable;
			Drawable* drawable = drawables.getDrawable(atoi(idDrawable.c_str()));
			drawable->setCoordinates(xDrawable,yDrawable);
			drawable->setDraw(true);
			}
			break;
		case KILL:
			{
			std::string idDrawable; ss >> idDrawable;
			Drawable* drawable = drawables.getDrawable(atoi(idDrawable.c_str()));
			//TODO Por ahora lo dibujamos arafue
			drawable->setCoordinates(TILES_HORIZONTAL,TILES_VERTICAL);
			drawable->setDraw(true);
			}
			break;
		case SOUND:
			{
			std::string idSound; ss >> idSound;
			std::cout << "Tendria que reproducir el sonido " << idSound << std::endl;
			}
			break;
		case START_LEVEL_SCREEN:
			windowChangeSignal.emit(LEVEL_SCREEN_NAME);
			break;
		case BACK_TO_LEVEL_SELECTION:
			windowChangeSignal.emit(LEVEL_SELECTOR_SCREEN_NAME);
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

StringSignal MegamanClientModel::changeScreenSignal() {
	return windowChangeSignal;
}

void MegamanClientModel::connectServer(std::string ip, std::string port) {
	serverProxy = new Socket(ip, port);
	recibirServer = true;
	this->start();
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

void MegamanClientModel::serverSendKey(int keyCode) {
	if (serverProxy!=nullptr) {
		std::string mensaje = std::to_string(KEY_PRESSED);
		mensaje.append(" ");
		mensaje.append(std::to_string(keyCode));
		mensaje.append("\n");
		serverProxy->enviar(mensaje);
	}
}

