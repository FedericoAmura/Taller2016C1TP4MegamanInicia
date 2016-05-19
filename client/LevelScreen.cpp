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

	std::cout << "Creamos el socket" << std::endl;
	serverProxy = new Socket("127.0.0.1","4321");
	std::cout << "mandamos primer mensaje" << std::endl;
	serverProxy->enviar("nos conectamos en el juego\n");
	std::cout << "mandamos segundo mensaje" << std::endl;
	serverProxy->enviar("mando mensajes de prueba\n");
	std::cout << "terminamos de construir la pantalla" << std::endl;
}

void LevelScreen::startLevel() {
	serverConn = Glib::signal_timeout().connect(sigc::mem_fun(*this,&LevelScreen::update),1000);
}

bool LevelScreen::update() {
	const int width = Gdk::screen_width();
	const int height = Gdk::screen_height();

	int start, end;
	std::string aux = serverProxy->recibirHasta('\n');
	std::cout << "Recibimos: " << aux << std::endl;

	//Consigo las nuevas ubicaciones para los megamanes
	//X1
	start = 3;
	end = aux.find("-Y1");
	std::string posX1 = aux.substr(start,end-start);
	std::cout << "posX1: " << posX1 << std::endl;
	//Y1
	start = end+4;
	end = aux.find("/X2",start);
	std::string posY1 = aux.substr(start,end-start);
	std::cout << "posY1: " << posY1 << std::endl;
	//X2
	start = end+4;
	end = aux.find("-Y2",start);
	std::string posX2 = aux.substr(start,end-start);
	std::cout << "posX2: " << posX2 << std::endl;
	//Y2
	start = end+4;
	end = aux.length();
	std::string posY2 = aux.substr(start,end-start);
	std::cout << "posY2: " << posY2 << std::endl << std::endl;


	//Muevo el primer megaman
	move(megaman1,atoi(posX1.c_str())*(width/100),atoi(posY1.c_str())*(height/100));
	//Muevo el segundo megaman
	move(megaman2,atoi(posX2.c_str())*(width/100),atoi(posY2.c_str())*(height/100));

	//Mando mi velocidad segun las teclas que aprete

	serverProxy->enviar("Tic\n");

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

