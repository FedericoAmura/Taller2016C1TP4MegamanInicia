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

#include "../common/MegamanBeginsConstants.h"
#include "Drawables.h"

typedef unsigned int uint;

LevelScreen::LevelScreen(MegamanClientModel& model) :
model(model) {
	double tileWidth = ceil((double)Gdk::screen_width()/(double)TILES_HORIZONTAL);
	double tileHeight = ceil((double)Gdk::screen_height()/(double)TILES_VERTICAL);
	tileSize = std::max(tileHeight,tileWidth);

	//TODO Dibujamos el fondo del nivel, despues se va a pasar al modelo como el fondo
	levelBackground.setImage("../images/background1.jpg",Gdk::screen_width(),Gdk::screen_height(),false);
	put(levelBackground,0,0);
}

void LevelScreen::startLevel() {
	//Refresco la pantalla cada 15 milisegundos (>60fps)
	updateScreenConn = Glib::signal_timeout().connect(sigc::mem_fun(*this,&LevelScreen::update),15);
}

bool LevelScreen::update() {
	for (int i = 0; i < model.getDrawables().size(); ++i) {
		Drawable* drawable = model.getDrawables().getDrawable(i);
		if (!drawable) continue;	//Fix hasta implementar el iterador
		if (drawable->shouldDraw()) {
			int drawableX = (int) (drawable->getX()*tileSize+0.5);
			int drawableY = (int) (drawable->getY()*tileSize+0.5);
			if (drawable->isDrawed()) {
				move(drawable->getImage(),drawableX,drawableY);
			} else {
				put(drawable->getImage(),drawableX,drawableY);
				drawable->setIsDrawed(true);
				drawable->getImage().show();
			}
			drawable->setDraw(false);
		}
		if (drawable->getSpriteId()>=(uint)9000) {
			//TODO esto deberia levantar los megamanes, chequear
			drawable->getImage().get_window()->raise();
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

