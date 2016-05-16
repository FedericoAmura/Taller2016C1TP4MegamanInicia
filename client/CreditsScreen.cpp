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

	creditsBackground.setImage("../images/creditsbackground.jpg",width,height);
	put(creditsBackground,0,0);
	credits.set_label("Creditos\nMegaman Inicia\nTaller TP4");
	put(credits,0.6*width,0.2*height);
	backButton.set_label("Back");
	put(backButton,0.05*width,0.05*height);
}

Gtk::Button& CreditsScreen::getBackButton() {
	return backButton;
}

CreditsScreen::~CreditsScreen() {
	// TODO Auto-generated destructor stub
}

