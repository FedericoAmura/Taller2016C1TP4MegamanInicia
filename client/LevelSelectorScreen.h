/*
 * LevelSelectorScreen.h
 *
 *  Created on: May 15, 2016
 *      Author: freddy
 */

#ifndef SRC_LEVELSELECTORSCREEN_H_
#define SRC_LEVELSELECTORSCREEN_H_

#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>

#include "MegamanClientModel.h"
#include "MyArea.h"

class LevelSelectorScreen : public Gtk::Grid {
private:
	MegamanClientModel& model;
	Gtk::Label messages;
	Drawing sparkManIcon;
	Gtk::Button sparkManButton;
	Drawing snakeManIcon;
	Gtk::Button snakeManButton;
	Drawing needleManIcon;
	Gtk::Button needleManButton;
	Drawing hardManIcon;
	Gtk::Button hardManButton;
	Drawing megaManIcon;
	Gtk::Button megaManButton;
	Drawing topManIcon;
	Gtk::Button topManButton;
	Drawing genimiManIcon;
	Gtk::Button geminiManButton;
	Drawing magnetManIcon;
	Gtk::Button magnetManButton;
	Drawing shadowManIcon;
	Gtk::Button shadowManButton;

public:
	LevelSelectorScreen(MegamanClientModel& model);
	Gtk::Button& getMegamanButton();
	virtual ~LevelSelectorScreen();
};

#endif /* SRC_LEVELSELECTORSCREEN_H_ */
