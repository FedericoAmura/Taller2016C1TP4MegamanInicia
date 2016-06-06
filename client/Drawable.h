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

class Drawable {
private:
	Drawing drawing;
	Mutex m;
	uint spriteId;
	double posX;
	double posY;
	bool drawed;		//indica si el drawable ya fue dibujado en un container
	bool changed;		//indica si el drawable deberia (re)dibujarse

public:
	Drawable();
	virtual ~Drawable();

	void setImage(uint spriteId, std::string ruta, int width, int height, bool flip);
	void setCoordinates(double x, double y);

	uint getSpriteId();
	Drawing& getImage();
	double getX();
	double getY();

	void setIsDrawed(bool isDrawed);
	void setChanged(bool modified);
	bool isDrawed();
	bool getChanged();


private:
	Drawable(const Drawable&);
	Drawable& operator=(const Drawable&);

};

#endif /* SRC_DRAWABLE_H_ */
