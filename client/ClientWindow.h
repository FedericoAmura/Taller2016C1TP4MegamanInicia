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

#include "ConnectionScreen.h"
#include "CreditsScreen.h"
#include "LevelScreen.h"
#include "LevelSelectorScreen.h"

class ClientWindow : public Gtk::Window {
private:
	Gtk::Stack screenContainer;
	ConnectionScreen connectionWindow;
	CreditsScreen creditsScreen;
	LevelSelectorScreen levelSelectorScreen;
	LevelScreen level;

public:
	ClientWindow();

	void showStart();
	void showCredits();
	void showLevelSelector();
	void showLevel();

	virtual ~ClientWindow();
};

#endif /* SRC_CLIENTWINDOW_H_ */
