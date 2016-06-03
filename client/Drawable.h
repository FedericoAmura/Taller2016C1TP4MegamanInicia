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
#include "../common/MyArea.h"

class Drawable {
private:
	Drawing drawing;
	Mutex m;
	double posX;
	double posY;
	bool drawed;	//indica si el drawable ya fue dibujado en un container
	bool draw;		//indica si el drawable deberia (re)dibujarse

public:
	Drawable();
	virtual ~Drawable();

	void setImage(std::string ruta, int width, int height, bool flip);
	void setCoordinates(double x, double y);

	Drawing& getImage();
	double getX();
	double getY();

	void setIsDrawed(bool isDrawed);
	void setDraw(bool shouldDraw);
	bool isDrawed();
	bool shouldDraw();


private:
	Drawable(const Drawable&);
	Drawable& operator=(const Drawable&);

};

#endif /* SRC_DRAWABLE_H_ */
