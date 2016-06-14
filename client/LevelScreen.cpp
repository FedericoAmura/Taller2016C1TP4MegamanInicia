/*
 * LevelScreen.cpp
 *
 *  Created on: May 15, 2016
 *      Author: freddy
 */

#include "LevelScreen.h"

#include <gdkmm/general.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>

#include "../common/MegamanBeginsConstants.h"
#include "Drawables.h"

typedef unsigned int uint;

LevelScreen::LevelScreen(MegamanClientModel& model) :
	model(model) {
	double tileWidth = ceil((double)Gdk::screen_width()/(double)TILES_HORIZONTAL);
	double tileHeight = ceil((double)Gdk::screen_height()/(double)TILES_VERTICAL);
	tileSize = std::max(tileHeight,tileWidth);

	model.changeHealthSignal().connect(sigc::mem_fun(*this,&LevelScreen::setHealth));
	model.changeBackgroundSignal().connect(sigc::mem_fun(*this,&LevelScreen::setBackground));

	blackBackground.setImage("../sprites/level/background/city.png",Gdk::screen_width(),Gdk::screen_height(),false);
	put(blackBackground,0,0);
}

LevelScreen::~LevelScreen() {
}

void LevelScreen::startLevel() {
	//Refresco la pantalla cada 15 milisegundos (>60fps)
	updateScreenConn = Glib::signal_timeout().connect(sigc::mem_fun(*this,&LevelScreen::update),15);
}

void LevelScreen::stopLevel() {
	DrawablesIterator iter = model.getDrawables().drawablesIterator();
	for (int i = 0; i < model.getDrawables().size(); ++i) {
		Drawable* drawable = (*iter).second;
		if (drawable != nullptr) {
			drawable->setCoordinates(TILES_HORIZONTAL,TILES_VERTICAL);
			drawable->setChanged(true);
			drawable->setIsDrawed(false);
			remove(drawable->getImage());
		}
		++iter;
	}
	model.getDrawables().clear();
	updateScreenConn.disconnect();
}

bool LevelScreen::update() {
	DrawablesIterator iter = model.getDrawables().drawablesIterator();
	for (int i = 0; i < model.getDrawables().size(); ++i) {
		Drawable* drawable = (*iter).second;
		if (drawable != nullptr) {
			//Saco los megamanes y enemigos para siempre redibujarlos y asi tenerlos al frente
			if ((drawable->getSpriteId()>=(uint)9000 || drawable->getSpriteId()<(uint)2000) && drawable->isDrawed()) {
				remove(drawable->getImage());
				drawable->setIsDrawed(false);
				drawable->setChanged(true);
			}
			if (drawable->getChanged()) {
				int drawableX = (int) (drawable->getX()*tileSize+0.5);
				int drawableY = (int) (drawable->getY()*tileSize+0.5);
				if (drawable->isDrawed()) {
					move(drawable->getImage(),drawableX,drawableY);
				} else {
					put(drawable->getImage(),drawableX,drawableY);
					drawable->setIsDrawed(true);
					drawable->getImage().show();
				}
				drawable->setChanged(false);
			}
		}
		++iter;
	}
	return true;
}

void LevelScreen::setHealth(int id, int health) {
	//Armo un widget para la salud y lo dibujo
	std::cout << "Cambio la vida de " << id << " a " << health << "%"<< std::endl;
}

void LevelScreen::setBackground(std::string levelId) {
	//levelBackground.setImage("../sprites/level/background/rock.png",Gdk::screen_width(),Gdk::screen_height(),false);
	//put(levelBackground,0,0);
}

