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

LevelScreen::LevelScreen(MegamanClientModel& model) :
	model(model),
	offset(0) {
	tileSize = (double)Gdk::screen_height()/(double)TILES_VERTICAL;

	offset = (Gdk::screen_height()-tileSize*TILES_VERTICAL)/2;

	blackBackground.setImage("../sprites/level/background/blackBackground.png",Gdk::screen_width(),Gdk::screen_height(),false);
	background.put(blackBackground,0,0);
	put(background,0,offset);
	put(terrain,0,offset);
	put(foreground,0,offset);
}

LevelScreen::~LevelScreen() {
}

void LevelScreen::startLevel() {
	//Refresco la pantalla cada 15 milisegundos (>60fps)
	updateScreenConn = Glib::signal_timeout().connect(sigc::mem_fun(*this,&LevelScreen::update),15);
}

void LevelScreen::stopLevel() {
	Gtk::Fixed* layer;
	DrawablesIterator iter = model.getDrawables().drawablesIterator();
	for (int i = 0; i < model.getDrawables().size(); ++i) {
		Drawable* drawable = (*iter).second;
		if (drawable != nullptr) {
			int spriteID = drawable->getSpriteId();
			//Consigo el layer
			if (spriteID>=7000 && spriteID<8000) layer = &background;
			else if (spriteID>=4000 && spriteID<6000) layer = &terrain;
			else layer = &foreground;
			//Lo borro
			drawable->setCoordinates(TILES_HORIZONTAL,TILES_VERTICAL);
			drawable->setChanged(true);
			drawable->setIsDrawed(false);
			try {layer->remove(drawable->getImage());}catch(...){}
		}
		++iter;
	}
	model.getDrawables().clear();
	updateScreenConn.disconnect();
}

bool LevelScreen::update() {
	Gtk::Fixed* layer;
	DrawablesIterator iter = model.getDrawables().drawablesIterator();
	for (int i = 0; i < model.getDrawables().size(); ++i) {
		Drawable* drawable = (*iter).second;
		if (drawable != nullptr) {
			int spriteID = drawable->getSpriteId();
			//Consigo el layer
			if (spriteID>=7000 && spriteID<8000) layer = &background;
			else if (spriteID>=4000 && spriteID<6000) layer = &terrain;
			else layer = &foreground;
			//Aplico operacion si cambio
			if (drawable->getChanged()) {
				int drawableX = (int) (drawable->getX()*tileSize+0.5);
				int drawableY = (int) (drawable->getY()*tileSize+0.5);
				if (drawable->isDrawed()) {	//ya estaba dibujado, solo muevo
					try{layer->move(drawable->getImage(),drawableX,drawableY);}catch(...){}
				} else {					//no esta dibujado, dibujo
					try{
						layer->put(drawable->getImage(),drawableX,drawableY);
						drawable->setIsDrawed(true);
						drawable->getImage().show();
					}catch(...){}
				}
				drawable->setChanged(false);
			}
		}
		++iter;
	}
	return true;
}

