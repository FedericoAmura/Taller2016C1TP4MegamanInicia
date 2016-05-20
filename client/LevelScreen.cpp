/*
 * LevelScreen.cpp
 *
 *  Created on: May 15, 2016
 *      Author: freddy
 */

#include "LevelScreen.h"

#include <gdkmm/general.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstdlib>
#include <glog/logging.h>

LevelScreen::LevelScreen() {
	const int width = Gdk::screen_width();
	const int height = Gdk::screen_height();

	//Dibujamos el fondo del nivel
	levelBackground.setImage("../images/background1.jpg",width,height);
	put(levelBackground,0,0);

	megaman1.setImage("../images/megaman1.png",207,238);
	megaman2.setImage("../images/megaman2.png",207,238);
	put(megaman1,width/4,height/4);
	put(megaman2,width/2,height/2);

	LOG(INFO) << "Creamos el socket";
	serverProxy = new Socket("127.0.0.1","4321");
	LOG(INFO) << "mandamos primer mensaje";
	serverProxy->enviar("nos conectamos en el juego\n");
	LOG(INFO) << "mandamos segundo mensaje";
	serverProxy->enviar("mando mensajes de prueba\n");
	LOG(INFO) << "terminamos de construir la pantalla";
}

void LevelScreen::startLevel() {
	serverConn = Glib::signal_timeout().connect(sigc::mem_fun(*this,&LevelScreen::update),100);
}

bool LevelScreen::update() {
	LOG(INFO)<<"empezo rutina update";
	const int width = Gdk::screen_width();
	const int height = Gdk::screen_height();

	int start, end;
	std::string aux = serverProxy->recibirHasta('\n');
	LOG(INFO) << "Recibimos: " << aux;

	//Consigo las nuevas ubicaciones para los megamanes
	//X1
	start = 3;
	end = aux.find("-Y1");
	std::string posX1 = aux.substr(start,end-start);
	LOG(INFO) << "posX1: " << posX1;
	//Y1
	start = end+4;
	end = aux.find("/X2",start);
	std::string posY1 = aux.substr(start,end-start);
	LOG(INFO) << "posY1: " << posY1;
	//X2
	start = end+4;
	end = aux.find("-Y2",start);
	std::string posX2 = aux.substr(start,end-start);
	LOG(INFO)<< "posX2: " << posX2;
	//Y2
	start = end+4;
	end = aux.length();
	std::string posY2 = aux.substr(start,end-start);
	LOG(INFO) << "posY2: " << posY2 ;


	//Muevo el primer megaman
	move(megaman1,atoi(posX1.c_str())*(width/100),atoi(posY1.c_str())*(height/100));
	//Muevo el segundo megaman
	move(megaman2,atoi(posX2.c_str())*(width/100),atoi(posY2.c_str())*(height/100));

	//Mando mi velocidad segun las teclas que aprete

	serverProxy->enviar("Tic\n");
	LOG(INFO)<<"termino rutina update";
	return true;
}

void LevelScreen::stopLevel() {
	//TODO que se saque todos los widgets que hay graficados, ya no nos ven
	serverConn.disconnect();
}

bool LevelScreen::keyPress() {
	serverProxy->enviar("FIRE\n");
	return true;
}

LevelScreen::~LevelScreen() {
	serverProxy->cerrar();
	delete(serverProxy);
}

