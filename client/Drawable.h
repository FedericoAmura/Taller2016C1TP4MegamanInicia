/*
 * Drawable.h
 *
 *  Created on: May 19, 2016
 *      Author: freddy
 */

#ifndef SRC_DRAWABLE_H_
#define SRC_DRAWABLE_H_

#include <string>

#include "Mutex.h"
#include "MyArea.h"

class Drawable {
private:
	Drawing drawing;
	Mutex m;
	std::string posX;
	std::string posY;
	bool dibujado;
	bool isForeGround;

public:
	Drawable();
	void setIsDrawed(bool isDrawed);
	bool isDrawed();
	void setImage(std::string ruta, int width, int height);
	void setCoordinates(const std::string &x, const std::string &y);
	Drawing& getImage();
	int getX();
	int getY();
	virtual ~Drawable();

private:
	Drawable(const Drawable&);
	Drawable& operator=(const Drawable&);

};

#endif /* SRC_DRAWABLE_H_ */
