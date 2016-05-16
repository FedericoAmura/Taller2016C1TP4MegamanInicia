/*
 * LevelScreen.h
 *
 *  Created on: May 15, 2016
 *      Author: freddy
 */

#ifndef SRC_LEVELSCREEN_H_
#define SRC_LEVELSCREEN_H_

#include <gtkmm/fixed.h>

#include "MyArea.h"
#include "Socket.h"

class LevelScreen : public Gtk::Fixed {
private:
	Drawing levelBackground;
	Drawing megaman1;
	Drawing megaman2;

public:
	LevelScreen();
	virtual ~LevelScreen();
};

#endif /* SRC_LEVELSCREEN_H_ */
