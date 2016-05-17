/*
 * ClientWindow.cpp
 *
 *  Created on: May 10, 2016
 *      Author: freddy
 */

#include "ClientWindow.h"

#include <glibmm/signalproxy.h>
#include <glibmm/ustring.h>
#include <gtkmm/button.h>
#include <iostream>

ClientWindow::ClientWindow() {
	set_title("Megaman Begins");
	fullscreen();
	add(screenContainer);

	//Configuro senales de la pantalla de coneccion
	Gtk::Button &connServerButton = connectionWindow.getServerButton();
	connServerButton.signal_clicked().connect(sigc::mem_fun(*this,&ClientWindow::showLevelSelector));
	Gtk::Button &connCreditsButton = connectionWindow.getCreditsButton();
	connCreditsButton.signal_clicked().connect(sigc::mem_fun(*this,&ClientWindow::showCredits));
	Gtk::Button &connExitButton = connectionWindow.getExitButton();
	connExitButton.signal_clicked().connect(sigc::mem_fun(*this,&Gtk::Window::hide));

	//Configuro senales de la pantalla de creditos
	Gtk::Button &credBackButton = creditsScreen.getBackButton();
	credBackButton.signal_clicked().connect(sigc::mem_fun(*this,&ClientWindow::showStart));

	//Configuro senales para ir a nivel
	Gtk::Button &megamanButton = levelSelectorScreen.getMegamanButton();
	megamanButton.signal_clicked().connect(sigc::mem_fun(*this,&ClientWindow::showLevel));

	//Agrego las pantallas y activo la de coneccion
	screenContainer.add(connectionWindow,"connectionScreen");
	screenContainer.add(creditsScreen,"creditsScreen");
	screenContainer.add(levelSelectorScreen,"levelSelectorScreen");
	screenContainer.add(level,"levelScreen");
	screenContainer.set_visible_child("connectionScreen");

	show_all_children();
}

void ClientWindow::showStart() {
	screenContainer.set_visible_child("connectionScreen");
}

void ClientWindow::showCredits() {
	screenContainer.set_visible_child("creditsScreen");
}

void ClientWindow::showLevelSelector() {
	screenContainer.set_visible_child("levelSelectorScreen");
}

void ClientWindow::showLevel() {
	level.startLevel();
	screenContainer.set_visible_child("levelScreen");
}

void ClientWindow::cleanLevelScreen(){
	if (0==screenContainer.get_visible_child_name().compare("levelScreen")) {
		level.stopLevel();
	}
}

bool ClientWindow::on_key_press_event(GdkEventKey* key_event) {
	std::cout << "apretamos algo" << std::endl;
	if (key_event->keyval == GDK_KEY_1){
		std::cout << "ese algo fue 1" << std::endl;
		return level.keyPress();
	}
	return true;
}

ClientWindow::~ClientWindow() {
}

