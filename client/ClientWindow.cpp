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
connectionScreen(model),
levelSelectorScreen(model),
levelScreen(model) {
	set_title("Megaman Begins");
	fullscreen();
	add(screenContainer);
	//Pongo esta ventana a ver el evento de apretar algo
	add_events(Gdk::KEY_PRESS_MASK);

	//Conecto senales de la pantalla de coneccion
	Gtk::Button &connServerButton = connectionScreen.getServerButton();
	connServerButton.signal_clicked().connect(sigc::mem_fun(*this,&ClientWindow::connectModel));
	Gtk::Button &connCreditsButton = connectionScreen.getCreditsButton();
	connCreditsButton.signal_clicked().connect(sigc::bind<std::string>(sigc::mem_fun(*this,&ClientWindow::showScreen),CREDITS_SCREEN_NAME));
	Gtk::Button &connExitButton = connectionScreen.getExitButton();
	connExitButton.signal_clicked().connect(sigc::mem_fun(*this,&Gtk::Window::hide));

	//Conecto senales de la pantalla de creditos
	Gtk::Button &credBackButton = creditsScreen.getBackButton();
	credBackButton.signal_clicked().connect(sigc::bind<std::string>(sigc::mem_fun(*this,&ClientWindow::showScreen),CONNECTION_SCREEN_NAME));

	//Conecto senales para notificar al server de eleccion del nivel
	Gtk::Button &magnetManButton = levelSelectorScreen.getMagnetManButton();
	magnetManButton.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(model,&MegamanClientModel::serverSendLevelSelected),MAGNETMAN));
	Gtk::Button &sparkManButton = levelSelectorScreen.getSparkManButton();
	sparkManButton.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(model,&MegamanClientModel::serverSendLevelSelected),SPARKMAN));
	Gtk::Button &ringManButton = levelSelectorScreen.getRingManButton();
	ringManButton.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(model,&MegamanClientModel::serverSendLevelSelected),RINGMAN));
	Gtk::Button &fireManButton = levelSelectorScreen.getFireManButton();
	fireManButton.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(model,&MegamanClientModel::serverSendLevelSelected),FIREMAN));
	Gtk::Button &bombManButton = levelSelectorScreen.getBombManButton();
	bombManButton.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(model,&MegamanClientModel::serverSendLevelSelected),BOMBMAN));

	//Conecto senal del modelo para cambiar las ventanas
	model.changeScreenSignal().connect(sigc::mem_fun(*this,&ClientWindow::showScreen));

	//Agrego las pantallas y activo la de coneccion
	screenContainer.add(connectionScreen,CONNECTION_SCREEN_NAME);
	screenContainer.add(creditsScreen,CREDITS_SCREEN_NAME);
	screenContainer.add(levelSelectorScreen,LEVEL_SELECTOR_SCREEN_NAME);
	screenContainer.add(levelScreen,LEVEL_SCREEN_NAME);
	showScreen(CONNECTION_SCREEN_NAME);

	show_all_children();
}

void ClientWindow::showScreen(std::string childrenName) {
	screenContainer.set_visible_child(childrenName);
	if (childrenName == LEVEL_SCREEN_NAME)
		levelScreen.startLevel();
	else
		levelScreen.stopLevel();
}

void ClientWindow::connectModel() {
	std::string serverIP = connectionScreen.getServerIP();
	std::string serverPort = connectionScreen.getServerPort();
	model.connectServer(serverIP, serverPort);
	showScreen(LEVEL_SELECTOR_SCREEN_NAME);	//TODO mover al modelo
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

