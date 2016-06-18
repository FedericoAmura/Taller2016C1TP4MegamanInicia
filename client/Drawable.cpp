/*
 * Drawable.cpp
 *
 *  Created on: May 19, 2016
 *      Author: freddy
 */

#include "Drawable.h"

#include <iostream>

Drawable::Drawable(int offset) :
	imageId(0),
	offset(offset),
	posX(0.0),
	posY(0.0),
	flipped(false),
	drawed(false),
	changed(true) {
}

Drawable::~Drawable() {
}

void Drawable::setImage(int spriteId, SpriteDispenser &dispenser, bool flip) {
	imageId = spriteId;
	flipped = flip;
	Lock l(m);
	drawing.setImage(dispenser.get(imageId,offset), dispenser.getWidth(imageId), dispenser.getHeight(imageId), flipped);
}

void Drawable::setCoordinates(double x, double y) {
	Lock l(m);
	posX = x;
	posY = y;
}

int Drawable::getSpriteId() {
	return imageId;
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

bool Drawable::getFlipped() {
	Lock l(m);
	return flipped;
}

void Drawable::setIsDrawed(bool isDrawed) {
	Lock l(m);
	drawed = isDrawed;
}

void Drawable::setChanged(bool modified) {
	Lock l(m);
	changed = modified;
}

bool Drawable::isDrawed() {
	Lock l(m);
	return drawed;
}

bool Drawable::getChanged() {
	Lock l(m);
	return changed;
}

void Drawable::setPercent(int percent) {
	drawing.setPercent(percent);
}

