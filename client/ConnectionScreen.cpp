/*
 * ConnectionScreen.cpp
 *
 *  Created on: May 15, 2016
 *      Author: freddy
 */

#include "ConnectionScreen.h"

#include <gdkmm/general.h>


ConnectionScreen::ConnectionScreen() {
	const int width = Gdk::screen_width();
	const int height = Gdk::screen_height();

	//Dibujamos el fondo de la pantalla de inicio
	connectionBackground.setImage("../images/introbackground.jpg",width,height);
	put(connectionBackground,0,0);

	//Armo la box para la vinculacion
	serverLabel.set_label("Server IP:");
	serverAddress.set_max_length(15);
	serverButton.set_label("Connect");
	connectionContainer.set_spacing(8);
	connectionContainer.add(serverLabel);
	connectionContainer.add(serverAddress);
	connectionContainer.add(serverButton);
	put(connectionContainer,0.2*width,0.65*height);

	//Agrego el boton de salida y el de creditos
	creditsButton.set_label("Credits");
	exitButton.set_label("Exit");
	buttons.set_spacing(8);
	buttons.add(creditsButton);
	buttons.add(exitButton);
	put(buttons,0.9*width,0.05*height);
}

Gtk::Button& ConnectionScreen::getServerButton() {
	return serverButton;
}

Gtk::Button& ConnectionScreen::getCreditsButton() {
	return creditsButton;
}

Gtk::Button& ConnectionScreen::getExitButton() {
	return exitButton;
}

ConnectionScreen::~ConnectionScreen() {
	// TODO Auto-generated destructor stub
}

