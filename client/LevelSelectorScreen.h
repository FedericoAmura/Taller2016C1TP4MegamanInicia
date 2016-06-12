/*
 * LevelSelectorScreen.h
 *
 *  Created on: May 15, 2016
 *      Author: freddy
 */

#ifndef SRC_LEVELSELECTORSCREEN_H_
#define SRC_LEVELSELECTORSCREEN_H_

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>

#include "MegamanClientModel.h"
#include "../common/Drawing.h"

class LevelSelectorScreen : public Gtk::Grid {
private:
	MegamanClientModel& model;
	Gtk::VBox megamanContainer;
	Gtk::Button exitButton;
	Gtk::Label dataLabel;
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
	virtual ~LevelSelectorScreen();

	Gtk::Button& getDisconnectButton();
	Gtk::Button& getMagnetManButton();
	Gtk::Button& getSparkManButton();
	Gtk::Button& getRingManButton();
	Gtk::Button& getFireManButton();
	Gtk::Button& getBombManButton();

private:
	void fillText();
};

#endif /* SRC_LEVELSELECTORSCREEN_H_ */
