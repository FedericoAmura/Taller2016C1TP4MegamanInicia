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

	//TODO Dibujamos el fondo del nivel, despues se va a pasar al modelo como el fondo
	levelBackground.setImage("../images/background1.jpg",width,height,false);
	put(levelBackground,0,0);
}

void LevelScreen::startLevel() {
	//Refresco la pantalla cada 15 milisegundos (>60fps)
	updateScreenConn = Glib::signal_timeout().connect(sigc::mem_fun(*this,&LevelScreen::update),15);
}

bool LevelScreen::update() {
	const float width = (float) Gdk::screen_width();
	const float height = (float) Gdk::screen_height();

	for (int i = 0; i < model.getDrawables().size(); ++i) {
		Drawable* drawable = model.getDrawables().getDrawable(i);
		if (drawable->isDrawed()) {
			move(drawable->getImage(),drawable->getX()*(width/100),drawable->getY()*(height/100));
		} else {
			put(drawable->getImage(),drawable->getX()*(width/100),drawable->getY()*(height/100));
			drawable->setIsDrawed(true);
			drawable->getImage().show();
		}
	}

	return true;
}

void LevelScreen::stopLevel() {
	//TODO que se saque todos los widgets que hay graficados, ya no se ven
	/*for (int i = 0; i < model.getDrawables().size(); ++i) {
		Drawable* drawable = model.getDrawables().getDrawable(i);
		drawable->setIsDrawed(false);
		remove(drawable->getImage());
	}*/
	updateScreenConn.disconnect();
}

LevelScreen::~LevelScreen() {
}

