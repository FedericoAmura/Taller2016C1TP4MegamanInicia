/*
 * ConnectionScreen.cpp
 *
 *  Created on: May 15, 2016
 *      Author: freddy
 */

#include "ConnectionScreen.h"

#include <gdkmm/general.h>


ConnectionScreen::ConnectionScreen(MegamanClientModel& model) :
	model(model) {
	const int width = Gdk::screen_width();
	const int height = Gdk::screen_height();

	//Dibujamos el fondo de la pantalla de inicio
	connectionBackground.setImage("../images/introbackground.jpg",width,height,false);
	put(connectionBackground,0,0);

	//Armo la box para la vinculacion
	serverAddress.set_editable(true);
	serverAddress.set_placeholder_text("Server IP");
	serverAddress.set_max_length(15);
	serverPort.set_placeholder_text("Server Port");
	serverPort.set_max_length(5);
	//serverAddress.set_text("127.0.0.1");	//TODO asi ya lo tengo escrito
	//serverPort.set_text("4321");			//TODO asi ya lo tengo escrito
	serverButton.set_label("Connect");
	connectionContainer.set_spacing(8);
	connectionContainer.add(serverAddress);
	connectionContainer.add(serverPort);
	connectionContainer.add(serverButton);
	put(connectionContainer,0.15*width,0.65*height);

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

std::string ConnectionScreen::getServerIP() {
	return serverAddress.get_text();
}
std::string ConnectionScreen::getServerPort() {
	return serverPort.get_text();
}

ConnectionScreen::~ConnectionScreen() {
}

