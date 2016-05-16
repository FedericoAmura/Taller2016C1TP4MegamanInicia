/*
 * LevelScreen.cpp
 *
 *  Created on: May 15, 2016
 *      Author: freddy
 */

#include "LevelScreen.h"

#include <gdkmm/general.h>
#include <string>


LevelScreen::LevelScreen() {
	const int width = Gdk::screen_width();
	const int height = Gdk::screen_height();

	//Dibujamos el fondo del nivel
	levelBackground.setImage("../images/background1.jpg",width,height);
	put(levelBackground,0,0);

	megaman1.setImage("../images/megaman1.png",207,238);
	megaman2.setImage("../images/megaman2.png",207,238);
	put(megaman1,250,250);
	put(megaman2,width/2,height/2);
}

LevelScreen::~LevelScreen() {
}

