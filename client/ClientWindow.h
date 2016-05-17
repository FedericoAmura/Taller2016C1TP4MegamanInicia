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
#include <cstdbool>

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
	void cleanLevelScreen();

	virtual ~ClientWindow();

private:
	bool on_key_press_event(GdkEventKey* key_event) override;
};

#endif /* SRC_CLIENTWINDOW_H_ */
