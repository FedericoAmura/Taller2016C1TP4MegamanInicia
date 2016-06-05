/*
 * Drawable.cpp
 *
 *  Created on: May 19, 2016
 *      Author: freddy
 */

#include "Drawable.h"

#include <iostream>

Drawable::Drawable() :
	spriteId(0),
	posX(0.0),
	posY(0.0),
	drawed(false),
	draw(true) {
}

Drawable::~Drawable() {
}

void Drawable::setImage(uint spriteId, std::string ruta, int width, int height, bool flip) {
	this->spriteId = spriteId;
	Lock l(m);
	drawing.setImage(ruta, width, height, flip);
}

void Drawable::setCoordinates(double x, double y) {
	Lock l(m);
	posX = x;
	posY = y;
}

uint Drawable::getSpriteId() {
	return spriteId;
}

Drawing& Drawable::getImage() {
	Lock l(m);
	return drawing;
}

double Drawable::getX() {
	Lock l(m);
	return posX;
}

double Drawable::getY() {
	Lock l(m);
	return posY;
}

void Drawable::setIsDrawed(bool isDrawed) {
	Lock l(m);
	drawed = isDrawed;
}

void Drawable::setDraw(bool shouldDraw) {
	Lock l(m);
	draw = shouldDraw;
}

bool Drawable::isDrawed() {
	Lock l(m);
	return drawed;
}

bool Drawable::shouldDraw() {
	Lock l(m);
	return draw;
}

