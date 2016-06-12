/*
 * CreditsScreen.h
 *
 *  Created on: May 15, 2016
 *      Author: freddy
 */

#ifndef SRC_CREDITSSCREEN_H_
#define SRC_CREDITSSCREEN_H_

#include <gtkmm/button.h>
#include <gtkmm/fixed.h>
#include <gtkmm/label.h>

#include "../common/Drawing.h"

class CreditsScreen : public Gtk::Fixed {
private:
	Drawing creditsBackground;
	Gtk::Button backButton;

public:
	CreditsScreen();
	Gtk::Button& getBackButton();
	virtual ~CreditsScreen();
};

#endif /* SRC_CREDITSSCREEN_H_ */
