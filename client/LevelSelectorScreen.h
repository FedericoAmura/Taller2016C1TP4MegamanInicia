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
#include "../common/MyArea.h"

class LevelSelectorScreen : public Gtk::Grid {
private:
	MegamanClientModel& model;
	//Gtk::Label messages;
	Drawing megaManIcon;
	Gtk::Button megaManButton;
	Drawing magnetManIcon;
	Gtk::Button magnetManButton;
	Drawing sparkManIcon;
	Gtk::Button sparkManButton;
	Drawing ringManIcon;
	Gtk::Button ringManButton;
	Drawing fireManIcon;
	Gtk::Button fireManButton;
	Drawing bombManIcon;
	Gtk::Button bombManButton;

public:
	LevelSelectorScreen(MegamanClientModel& model);
	Gtk::Button& getMegamanButton();
	Gtk::Button& getMagnetManButton();
	Gtk::Button& getSparkManButton();
	Gtk::Button& getRingManButton();
	Gtk::Button& getFireManButton();
	Gtk::Button& getBombManButton();
	virtual ~LevelSelectorScreen();
};

#endif /* SRC_LEVELSELECTORSCREEN_H_ */
