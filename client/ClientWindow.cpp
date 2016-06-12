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
#include "../common/MegamanBeginsConstants.h"
#include "WindowNames.h"

ClientWindow::ClientWindow() :
connectionScreen(model),
levelSelectorScreen(model),
levelScreen(model) {
	set_title("Megaman Begins");
	fullscreen();
	add(screenContainer);

	//Pongo esta ventana a ver el evento de apretar algo e informo al modelo cada 100ms
	add_events(Gdk::KEY_PRESS_MASK);
	add_events(Gdk::KEY_RELEASE_MASK);
	updateKeyboardConn = Glib::signal_timeout().connect(sigc::mem_fun(*this,&ClientWindow::updateKeyboard),100);

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
	Gtk::Button &disconnectButton = levelSelectorScreen.getDisconnectButton();
	disconnectButton.signal_clicked().connect(sigc::mem_fun(*this,&ClientWindow::disconnectModel));
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

	//Conecto senal del modelo para definir el fondo del nivel
	model.setBackgroundSignal().connect(sigc::mem_fun(levelScreen,&LevelScreen::setBackground));
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

ClientWindow::~ClientWindow() {
}

void ClientWindow::showScreen(std::string childrenName) {
	Glib::RefPtr<Gdk::Cursor> cursor;
	screenContainer.set_visible_child(childrenName);
	if (childrenName == LEVEL_SCREEN_NAME) {
		levelScreen.startLevel();
		cursor = Gdk::Cursor::create(Gdk::BLANK_CURSOR);
	} else {
		levelScreen.stopLevel();
		cursor = Gdk::Cursor::create(Gdk::ARROW);
	}

	Glib::RefPtr<Gdk::Window> window = get_window();
	if (window) window->set_cursor(cursor);
}

void ClientWindow::connectModel() {
	std::string serverIP = connectionScreen.getServerIP();
	std::string serverPort = connectionScreen.getServerPort();
	try {
		model.connectServer(serverIP, serverPort);
		showScreen(LEVEL_SELECTOR_SCREEN_NAME);
	} catch (std::exception &e) {
		//No nos pudimos conectar al server
	}
}

void ClientWindow::disconnectModel() {
	model.disconnectServer();
	showScreen(CONNECTION_SCREEN_NAME);
}

bool ClientWindow::on_key_press_event(GdkEventKey* key_event) {
	guint keyVal = key_event->keyval;

	if (keyVal == GDK_KEY_space) keyboard.setState(KEY_SPACE_ID,true);
	else if (keyVal == GDK_KEY_Up) keyboard.setState(KEY_UP_ID,true);
	else if (keyVal == GDK_KEY_Right) keyboard.setState(KEY_RIGHT_ID,true);
	else if (keyVal == GDK_KEY_Down) keyboard.setState(KEY_DOWN_ID,true);
	else if (keyVal == GDK_KEY_Left) keyboard.setState(KEY_LEFT_ID,true);
	else if (keyVal == GDK_KEY_1) keyboard.setState(KEY_1_ID,true);
	else if (keyVal == GDK_KEY_2) keyboard.setState(KEY_2_ID,true);
	else if (keyVal == GDK_KEY_3) keyboard.setState(KEY_3_ID,true);
	else if (keyVal == GDK_KEY_4) keyboard.setState(KEY_4_ID,true);
	else if (keyVal == GDK_KEY_5) keyboard.setState(KEY_5_ID,true);
	else if (keyVal == GDK_KEY_Escape) keyboard.setState(KEY_ESC_ID,true);

	return Gtk::Window::on_key_press_event(key_event);
}

bool ClientWindow::on_key_release_event(GdkEventKey* key_event) {
	guint keyVal = key_event->keyval;

	if (keyVal == GDK_KEY_space) keyboard.setState(KEY_SPACE_ID,false);
	else if (keyVal == GDK_KEY_Up) keyboard.setState(KEY_UP_ID,false);
	else if (keyVal == GDK_KEY_Right) keyboard.setState(KEY_RIGHT_ID,false);
	else if (keyVal == GDK_KEY_Down) keyboard.setState(KEY_DOWN_ID,false);
	else if (keyVal == GDK_KEY_Left) keyboard.setState(KEY_LEFT_ID,false);
	else if (keyVal == GDK_KEY_1) keyboard.setState(KEY_1_ID,false);
	else if (keyVal == GDK_KEY_2) keyboard.setState(KEY_2_ID,false);
	else if (keyVal == GDK_KEY_3) keyboard.setState(KEY_3_ID,false);
	else if (keyVal == GDK_KEY_4) keyboard.setState(KEY_4_ID,false);
	else if (keyVal == GDK_KEY_5) keyboard.setState(KEY_5_ID,false);
	else if (keyVal == GDK_KEY_Escape) keyboard.setState(KEY_ESC_ID,false);

	return Gtk::Window::on_key_release_event(key_event);
}

bool ClientWindow::updateKeyboard() {
	model.serverSendKeyboard((int)keyboard.getKeyboardState());
	return true;
}

