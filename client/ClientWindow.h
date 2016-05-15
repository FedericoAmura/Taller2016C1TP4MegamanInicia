/*
 * ClientWindow.h
 *
 *  Created on: May 10, 2016
 *      Author: freddy
 */

#ifndef SRC_CLIENTWINDOW_H_
#define SRC_CLIENTWINDOW_H_

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/stack.h>
#include <gtkmm/window.h>

#include "MyArea.h"
#include "WidgetGrid.h"

class ClientWindow : public Gtk::Window {
private:
	Gtk::Stack selector;

	//Pantalla de coneccion
	WidgetGrid connectionGrid;
	Drawing connectionBackground;
	Gtk::Box connectionContainer;
	Gtk::Label serverLabel;
	Gtk::Entry serverAddress;
	Gtk::Button serverButton;
	Gtk::Box buttons;
	Gtk::Button creditsButton;
	Gtk::Button exitButton;

	//Pantalla de seleccion de nivel
	Gtk::Grid levelSelectorGrid;
	Gtk::Label messages;
	Drawing sparkManIcon;
	Gtk::Button sparkManButton;
	Drawing snakeManIcon;
	Gtk::Button snakeManButton;
	Drawing needleManIcon;
	Gtk::Button needleManButton;
	Drawing hardManIcon;
	Gtk::Button hardManButton;
	Drawing megaManIcon;
	Gtk::Button megaManButton;
	Drawing topManIcon;
	Gtk::Button topManButton;
	Drawing genimiManIcon;
	Gtk::Button geminiManButton;
	Drawing magnetManIcon;
	Gtk::Button magnetManButton;
	Drawing shadowManIcon;
	Gtk::Button shadowManButton;

	//Pantalla de nivel
	Drawing nivel;

	//Pantalla de creditos
	WidgetGrid creditsGrid;
	Drawing creditsBackground;
	Gtk::Label credits;
	Gtk::Button backButton;

public:
	ClientWindow();

	void showStart();
	void showCredits();
	void showLevelSelector();
	void showLevel();

	virtual ~ClientWindow();
};

#endif /* SRC_CLIENTWINDOW_H_ */
