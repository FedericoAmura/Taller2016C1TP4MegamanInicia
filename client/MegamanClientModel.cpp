/*
 * MegamanClientModel.cpp
 *
 *  Created on: May 18, 2016
 *      Author: freddy
 */

#include "MegamanClientModel.h"

#include <iostream>

#include "ClientKeyCodes.h"

MegamanClientModel::MegamanClientModel() :
serverProxy(nullptr) {

	//Pongo 2 megamanes para probar
	Drawable* megamanRandom = new Drawable();
	megamanRandom->setImage("../sprites/megaman pc/megaman_idle.png",50,52);
	megamanRandom->setCoordinates("20","20");
	drawables.setDrawable(0,megamanRandom);

	Drawable* megamanUser = new Drawable();
	megamanUser->setImage("../sprites/megaman pc/megaman_attack0.png",66,52);
	megamanRandom->setCoordinates("50","50");
	drawables.setDrawable(1,megamanUser);
}

MegamanClientModel::~MegamanClientModel() {
	serverReceiver.disconnect();
	serverProxy->cerrar();
	if (serverProxy!=nullptr) delete(serverProxy);
	serverProxy = nullptr;
}

Drawables& MegamanClientModel::getDrawables() {
	return drawables;
}

bool MegamanClientModel::updateDrawables() {
	int start, end;
	serverProxy->enviar("Update\n");
	std::string aux = serverProxy->recibirHasta('\n');
	std::cout << aux << std::endl;

	//Consigo las nuevas ubicaciones para los megamanes
	//X1
	start = 3;
	end = aux.find("-Y1");
	std::string posX1 = aux.substr(start,end-start);
	//std::cout << "posX1: " << posX1 << std::endl;
	//Y1
	start = end+4;
	end = aux.find("/X2",start);
	std::string posY1 = aux.substr(start,end-start);
	//std::cout << "posY1: " << posY1 << std::endl;
	//X2
	start = end+4;
	end = aux.find("-Y2",start);
	std::string posX2 = aux.substr(start,end-start);
	//std::cout << "posX2: " << posX2 << std::endl;
	//Y2
	start = end+4;
	end = aux.length();
	std::string posY2 = aux.substr(start,end-start);
	//std::cout << "posY2: " << posY2 << std::endl;

	drawables.getDrawable(1)->setCoordinates(posX1, posY1);
	drawables.getDrawable(0)->setCoordinates(posX2, posY2);
	return true;
}

void MegamanClientModel::connectServer(std::string ip, std::string port) {
	serverProxy = new Socket(ip, port);
	serverReceiver = Glib::signal_timeout().connect(sigc::mem_fun(*this,&MegamanClientModel::updateDrawables),15);
}

void MegamanClientModel::disconnectServer() {
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

