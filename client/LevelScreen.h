/*
 * LevelScreen.h
 *
 *  Created on: May 15, 2016
 *      Author: freddy
 */

#ifndef SRC_LEVELSCREEN_H_
#define SRC_LEVELSCREEN_H_

#include <gtkmm/fixed.h>
#include <glibmm/main.h>
#include <gdkmm/event.h>
#include <cstdbool>

#include "MyArea.h"
#include "Socket.h"

class LevelScreen : public Gtk::Fixed {
private:
	Drawing levelBackground;
	Drawing megaman1;
	Drawing megaman2;
	sigc::connection serverConn;
	Socket* serverProxy;

public:
	LevelScreen();
	void startLevel();
	void stopLevel();
	bool update();
	bool keyPress();
	virtual ~LevelScreen();
};

#endif /* SRC_LEVELSCREEN_H_ */
