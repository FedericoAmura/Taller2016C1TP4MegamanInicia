/*
 * Drawables.cpp
 *
 *  Created on: May 18, 2016
 *      Author: freddy
 */

#include "Drawables.h"

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

Drawable* Drawables::getDrawable(int ID) {
	Lock l(m);
	return drawableContainer[ID];
}

