/*
 * ClientWindow.h
 *
 *  Created on: May 10, 2016
 *      Author: freddy
 */

#ifndef SRC_CLIENTWINDOW_H_
#define SRC_CLIENTWINDOW_H_

#include <gdk/gdk.h>
#include <gdkmm/event.h>
#include <gdkmm.h>
#include <gtkmm/stack.h>
#include <gtkmm/window.h>
#include <cstdbool>
#include <string>

#include "ConnectionScreen.h"
#include "CreditsScreen.h"
#include "KeyMap.h"
#include "LevelScreen.h"
#include "LevelSelectorScreen.h"
#include "MegamanClientModel.h"

class ClientWindow : public Gtk::Window {
private:
	MegamanClientModel model;
	KeyMap keyboard;
	sigc::connection updateKeyboardConn;

	Gtk::Stack screenContainer;
	ConnectionScreen connectionScreen;
	CreditsScreen creditsScreen;
	LevelSelectorScreen levelSelectorScreen;
	LevelScreen levelScreen;

public:
	ClientWindow();
	virtual ~ClientWindow();

	void showScreen(std::string childrenName);
	void connectModel();
	void disconnectModel();

private:
	bool on_key_press_event(GdkEventKey* key_event);
	bool on_key_release_event(GdkEventKey* key_event);
	bool updateKeyboard();
};

#endif /* SRC_CLIENTWINDOW_H_ */
