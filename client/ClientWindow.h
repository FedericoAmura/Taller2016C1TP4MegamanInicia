/*
 * ClientWindow.h
 *
 *  Created on: May 10, 2016
 *      Author: freddy
 */

#ifndef SRC_CLIENTWINDOW_H_
#define SRC_CLIENTWINDOW_H_

#include <gtkmm/stack.h>
#include <gtkmm/window.h>
#include <gdkmm/event.h>
#include <gdkmm.h>
#include <gdk/gdk.h>
#include <cstdbool>

#include "ConnectionScreen.h"
#include "CreditsScreen.h"
#include "LevelScreen.h"
#include "LevelSelectorScreen.h"
#include "MegamanClientModel.h"
#include "WindowNames.h"

class ClientWindow : public Gtk::Window {
private:
	MegamanClientModel model;
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
	void cleanLevelScreen();

private:
	bool on_key_press_event(GdkEventKey* key_event);
};

#endif /* SRC_CLIENTWINDOW_H_ */
