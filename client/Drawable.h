/*
 * Drawable.h
 *
 *  Created on: May 19, 2016
 *      Author: freddy
 */

#ifndef SRC_DRAWABLE_H_
#define SRC_DRAWABLE_H_

#include <string>

#include "../common/Thread.h"
#include "../common/Drawing.h"
#include "../common/SpriteDispenser.h"

typedef unsigned int uint;

class Drawable {
private:
	Drawing drawing;
	Mutex m;
	uint imageId;
	uint offset;
	double posX;
	double posY;
	bool flipped;
	bool drawed;		//indica si el drawable ya fue dibujado en un container
	bool changed;		//indica si el drawable deberia (re)dibujarse

public:
	Drawable(uint offset = 0);
	virtual ~Drawable();

	void setImage(uint spriteId, SpriteDispenser &dispenser, bool flip);
	void setCoordinates(double x, double y);

	uint getSpriteId();
	Drawing& getImage();
	double getX();
	double getY();
	bool getFlipped();

	void setIsDrawed(bool isDrawed);
	void setChanged(bool modified);
	bool isDrawed();
	bool getChanged();
	void setPercent(int percent);


private:
	Drawable(const Drawable&);
	Drawable& operator=(const Drawable&);

};

#endif /* SRC_DRAWABLE_H_ */
