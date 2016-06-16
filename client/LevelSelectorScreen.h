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

class LevelSelectorScreen : public Gtk::HBox {
private:
	MegamanClientModel& model;
	Gtk::VBox firstColumn;
	Drawing fireManIcon;
	Gtk::Button fireManButton;
	Drawing ringManIcon;
	Gtk::Button ringManButton;

	Gtk::VBox secondColumn;
	Drawing header;
	Gtk::Label instructionLabel;
	Drawing magnetManIcon;
	Gtk::Button magnetManButton;
	Gtk::Label dataLabel;
	Gtk::HBox players;
	std::vector<Drawing*> playersAvatars;
	Gtk::Button exitButton;


	Gtk::VBox thirdColumn;
	Drawing sparkManIcon;
	Gtk::Button sparkManButton;
	Drawing bombManIcon;
	Gtk::Button bombManButton;

public:
	LevelSelectorScreen(MegamanClientModel& model);
	virtual ~LevelSelectorScreen();

	Gtk::Button& getDisconnectButton();

private:
	void fillStatus();
};

#endif /* SRC_LEVELSELECTORSCREEN_H_ */
