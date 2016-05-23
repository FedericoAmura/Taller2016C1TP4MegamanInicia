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

#include "../common/CommunicationCodes.h"

ClientWindow::ClientWindow() :
	connectionWindow(model),
	levelSelectorScreen(model),
	levelScreen(model) {
	set_title("Megaman Begins");
	fullscreen();
	add(screenContainer);
	//Pongo esta ventana a ver el evento de apretar algo
	add_events(Gdk::KEY_PRESS_MASK);

	//Conecto senales de la pantalla de coneccion
	Gtk::Button &connServerButton = connectionWindow.getServerButton();
	connServerButton.signal_clicked().connect(sigc::mem_fun(*this,&ClientWindow::startGameAndShowLevelSelector));
	Gtk::Button &connCreditsButton = connectionWindow.getCreditsButton();
	connCreditsButton.signal_clicked().connect(sigc::mem_fun(*this,&ClientWindow::showCreditsScreen));
	Gtk::Button &connExitButton = connectionWindow.getExitButton();
	connExitButton.signal_clicked().connect(sigc::mem_fun(*this,&Gtk::Window::hide));

	//Conecto senales de la pantalla de creditos
	Gtk::Button &credBackButton = creditsScreen.getBackButton();
	credBackButton.signal_clicked().connect(sigc::mem_fun(*this,&ClientWindow::showStartScreen));

	//Conecto senales para ir a nivel
	Gtk::Button &megamanButton = levelSelectorScreen.getMegamanButton();
	megamanButton.signal_clicked().connect(sigc::mem_fun(*this,&ClientWindow::showLevel));

	//Agrego las pantallas y activo la de coneccion
	screenContainer.add(connectionWindow,"connectionScreen");
	screenContainer.add(creditsScreen,"creditsScreen");
	screenContainer.add(levelSelectorScreen,"levelSelectorScreen");
	screenContainer.add(levelScreen,"levelScreen");
	screenContainer.set_visible_child("connectionScreen");

	show_all_children();
}

void ClientWindow::showStartScreen() {
	screenContainer.set_visible_child("connectionScreen");
}

void ClientWindow::showCreditsScreen() {
	screenContainer.set_visible_child("creditsScreen");
}

void ClientWindow::startGameAndShowLevelSelector() {
	std::string serverIP = connectionWindow.getServerIP();
	std::string serverPort = connectionWindow.getServerPort();
	model.connectServer(serverIP, serverPort);
	screenContainer.set_visible_child("levelSelectorScreen");
}

void ClientWindow::showLevel() {
	levelScreen.startLevel();
	screenContainer.set_visible_child("levelScreen");
}

void ClientWindow::cleanLevelScreen(){
	if (0==screenContainer.get_visible_child_name().compare("levelScreen")) {
		levelScreen.stopLevel();
	}
}

bool ClientWindow::on_key_press_event(GdkEventKey* key_event) {
	guint keyVal = key_event->keyval;
	if (keyVal == GDK_KEY_Up) {
		model.serverSendKey(KEY_UP);
	} else if (keyVal == GDK_KEY_Right) {
		model.serverSendKey(KEY_RIGHT);
	} else if (keyVal == GDK_KEY_Down) {
		model.serverSendKey(KEY_DOWN);
	} else if (keyVal == GDK_KEY_Left) {
		model.serverSendKey(KEY_LEFT);
	} else if (keyVal == GDK_KEY_space) {
		model.serverSendKey(KEY_SPACE);
	} else if (keyVal == GDK_KEY_Escape) {
		model.serverSendKey(KEY_ESC);
	}
	return Gtk::Window::on_key_press_event(key_event);
}

ClientWindow::~ClientWindow() {
}

