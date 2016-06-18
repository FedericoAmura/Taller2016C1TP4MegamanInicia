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

class Drawable {
private:
	Drawing drawing;
	Mutex m;
	int imageId;
	int offset;
	double posX;
	double posY;
	bool flipped;
	bool drawed;		//indica si el drawable ya fue dibujado en un container
	bool changed;		//indica si el drawable deberia (re)dibujarse

public:
	Drawable(int offset = 0);
	virtual ~Drawable();

	void setImage(int spriteId, SpriteDispenser &dispenser, bool flip);
	void setCoordinates(double x, double y);

	int getSpriteId();
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
