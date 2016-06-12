/*
 * CreditsScreen.cpp
 *
 *  Created on: May 15, 2016
 *      Author: freddy
 */

#include "CreditsScreen.h"

#include <gdkmm/general.h>

CreditsScreen::CreditsScreen() {
	const int width = Gdk::screen_width();
	const int height = Gdk::screen_height();

	creditsBackground.setImage("../sprites/level/background/creditsbackground.png",width,height,false);
	put(creditsBackground,0,0);
	backButton.set_label("Back");
	put(backButton,0.05*width,0.05*height);
}

Gtk::Button& CreditsScreen::getBackButton() {
	return backButton;
}

CreditsScreen::~CreditsScreen() {
	// TODO Auto-generated destructor stub
}

