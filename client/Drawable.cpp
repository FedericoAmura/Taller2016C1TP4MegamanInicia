/*
 * Drawable.cpp
 *
 *  Created on: May 19, 2016
 *      Author: freddy
 */

#include "Drawable.h"

Drawable::Drawable() {
}

void Drawable::setImage(std::string ruta, int width, int height) {
	drawing.setImage(ruta, width, height);
}

void Drawable::setCoordinates(const std::string &x, const std::string &y) {
	posX = x;
	posY = y;
}

Drawing& Drawable::getImage() {
	return drawing;
}

int Drawable::getX() {
	return atoi(posX.c_str());
}

int Drawable::getY() {
	return atoi(posY.c_str());
}

Drawable::~Drawable() {
}

