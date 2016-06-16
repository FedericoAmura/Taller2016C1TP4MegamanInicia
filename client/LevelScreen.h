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

#include "MegamanClientModel.h"
#include "Drawable.h"
#include "../common/Drawing.h"
#include "Socket.h"

class LevelScreen : public Gtk::Fixed {
private:
	MegamanClientModel& model;
	sigc::connection updateScreenConn;
	Gtk::Fixed background;
	Gtk::Fixed terrain;
	Gtk::Fixed foreground;
	Drawing blackBackground;
	double tileSize;

public:
	LevelScreen(MegamanClientModel& model);
	virtual ~LevelScreen();

	void startLevel();
	void stopLevel();
	bool update();
};

#endif /* SRC_LEVELSCREEN_H_ */
