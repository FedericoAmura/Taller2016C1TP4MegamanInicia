/*
 * Drawable.cpp
 *
 *  Created on: May 19, 2016
 *      Author: freddy
 */

#include "Drawable.h"

Drawable::Drawable() :
	dibujado(false),
	isForeGround(true) {
}

Drawable::~Drawable() {
}

bool Drawable::isDrawed() {
	return dibujado;
}

void Drawable::setIsDrawed(bool isDrawed) {
	dibujado = isDrawed;
}

void Drawable::setImage(std::string ruta, int width, int height) {
	Lock l(m);
	drawing.setImage(ruta, width, height);
}

void Drawable::setCoordinates(const std::string &x, const std::string &y) {
	Lock l(m);
	posX = x;
	posY = y;
}

Drawing& Drawable::getImage() {
	Lock l(m);
	return drawing;
}

float Drawable::getX() {
	Lock l(m);
	return atof(posX.c_str());
}

float Drawable::getY() {
	Lock l(m);
	return atof(posY.c_str());
}

