/*
 * Drawables.cpp
 *
 *  Created on: May 18, 2016
 *      Author: freddy
 */

#include "Drawables.h"

#include "../common/MegamanBeginsConstants.h"

Drawables::Drawables() {
}

Drawables::~Drawables() {
}

void Drawables::setDrawable(int ID, Drawable* drawable) {
	Lock l(m);
	drawableContainer[ID] = drawable;
}

bool Drawables::hasDrawable(int ID) {
	Lock l(m);
	if (drawableContainer[ID] != 0)
		return true;
	return false;
}

int Drawables::size() {
	Lock l(m);
	return drawableContainer.size();
}

DrawablesIterator Drawables::drawablesIterator() {
	Lock l(m);
	return drawableContainer.begin();
}

void Drawables::clear() {
	Lock l(m);
	drawableContainer.clear();
}

Drawable* Drawables::getDrawable(int ID) {
	Lock l(m);
	return drawableContainer[ID];
}

bool Drawables::removeDrawable(int ID) {
	Lock l(m);
	Drawable* drawable = drawableContainer[ID];
	if (drawable == nullptr) return false;
	drawable->setCoordinates(TILES_HORIZONTAL,TILES_VERTICAL);
	drawable->setChanged(true);
	return false;
}

