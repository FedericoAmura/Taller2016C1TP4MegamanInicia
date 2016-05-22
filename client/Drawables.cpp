/*
 * Drawables.cpp
 *
 *  Created on: May 18, 2016
 *      Author: freddy
 */

#include "Drawables.h"

#include "Lock.h"

Drawables::Drawables() {
}

Drawables::~Drawables() {
}

void Drawables::setDrawable(int ID, Drawable* drawable) {
	Lock l(foregroundMutex);
	foreground[ID] = drawable;
}

bool Drawables::hasDrawable(int ID) {
	if (foreground[ID] != 0)
		return true;
	return false;
}

Drawable* Drawables::getDrawable(int ID) {
	return foreground[ID];
}

