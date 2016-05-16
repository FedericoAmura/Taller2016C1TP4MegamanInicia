/*
 * ConnectionScreen.h
 *
 *  Created on: May 15, 2016
 *      Author: freddy
 */

#ifndef SRC_CONNECTIONSCREEN_H_
#define SRC_CONNECTIONSCREEN_H_

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/fixed.h>
#include <gtkmm/label.h>

#include "MyArea.h"

class ConnectionScreen : public Gtk::Fixed {
private:
	Drawing connectionBackground;
	Gtk::Box connectionContainer;
	Gtk::Label serverLabel;
	Gtk::Entry serverAddress;
	Gtk::Button serverButton;
	Gtk::Box buttons;
	Gtk::Button creditsButton;
	Gtk::Button exitButton;

public:
	ConnectionScreen();
	Gtk::Button& getServerButton();
	Gtk::Button& getCreditsButton();
	Gtk::Button& getExitButton();
	virtual ~ConnectionScreen();
};

#endif /* SRC_CONNECTIONSCREEN_H_ */
