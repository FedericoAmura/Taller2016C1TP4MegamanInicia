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
#include "../common/Thread.h"

typedef std::map<int,Drawable*>::iterator DrawablesIterator;

class Drawables {
private:
	std::map<int,Drawable*> drawableContainer;
	Mutex m;

public:
	Drawables();
	void setDrawable(int ID, Drawable* drawable);
	bool hasDrawable(int ID);
	int size();
	DrawablesIterator drawablesIterator();
	void clear();
	Drawable* getDrawable(int ID);
	bool removeDrawable(int ID);
	virtual ~Drawables();
};

#endif /* SRC_DRAWABLES_H_ */
