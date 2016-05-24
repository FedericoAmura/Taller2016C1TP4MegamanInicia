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

#include "Drawables.h"

LevelScreen::LevelScreen(MegamanClientModel& model) :
model(model) {
	const int width = Gdk::screen_width();
	const int height = Gdk::screen_height();

	//Dibujamos el fondo del nivel, igual despues se va a pasar al modelo como el fondo
	levelBackground.setImage("../images/background1.jpg",width,height);
	put(levelBackground,0,0);
}

void LevelScreen::startLevel() {
	//Refresco la pantalla cada 15 milisegundos (>60fps)
	updateScreenConn = Glib::signal_timeout().connect(sigc::mem_fun(*this,&LevelScreen::update),15);
}

bool LevelScreen::update() {
	const float width = (float) Gdk::screen_width();
	const float height = (float) Gdk::screen_height();

	Drawable* megamanRandom = model.getDrawables().getDrawable(0);
	if (megamanRandom->isDrawed()) {
		move(megamanRandom->getImage(),megamanRandom->getX()*(width/100.0),megamanRandom->getY()*(height/100));
	} else {
		put(megamanRandom->getImage(),megamanRandom->getX()*(width/100.0),megamanRandom->getY()*(height/100));
		megamanRandom->setIsDrawed(true);
		megamanRandom->getImage().show();
	}

	Drawable* megamanUser = model.getDrawables().getDrawable(1);
	if (megamanUser->isDrawed()) {
		move(megamanUser->getImage(),megamanUser->getX()*(width/100),megamanUser->getY()*(height/100));
	} else {
		put(megamanUser->getImage(),megamanUser->getX()*(width/100),megamanUser->getY()*(height/100));
		megamanUser->setIsDrawed(true);
		megamanUser->getImage().show();
	}

	return true;
}

void LevelScreen::stopLevel() {
	//TODO que se saque todos los widgets que hay graficados, ya no se ven
	updateScreenConn.disconnect();
}

LevelScreen::~LevelScreen() {
}

