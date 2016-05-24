/*
 * Drawables.h
 *
 *  Created on: May 18, 2016
 *      Author: freddy
 */

#ifndef SRC_DRAWABLES_H_
#define SRC_DRAWABLES_H_

#include <map>

#include "Drawable.h"
#include "Thread.h"

class Drawables {
private:
	std::map<int,Drawable*> background;
	Mutex backgroundMutex;
	std::map<int,Drawable*> foreground;
	Mutex foregroundMutex;

public:
	Drawables();
	void setDrawable(int ID, Drawable* drawable);
	bool hasDrawable(int ID);
	Drawable* getDrawable(int ID);
	virtual ~Drawables();
};

#endif /* SRC_DRAWABLES_H_ */
