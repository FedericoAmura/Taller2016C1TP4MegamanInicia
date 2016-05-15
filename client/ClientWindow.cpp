/*
 * ClientWindow.cpp
 *
 *  Created on: May 10, 2016
 *      Author: freddy
 */

#include "ClientWindow.h"

#include <gdkmm/general.h>
#include <glibmm/signalproxy.h>
#include <gtkmm/enums.h>

ClientWindow::ClientWindow() {
	const int width = Gdk::screen_width();
	const int height = Gdk::screen_height();

	//Seteamos propiedades de la ventana
	set_title("Megaman Begins");
	fullscreen();
	add(selector);

	//Armamos la pantalla de conexion
	connectionGrid.set_name("connectionGrid");
	//Dibujamos el fondo de la pantalla de inicio
	connectionBackground.setImage("../images/introbackground.jpg",width,height);
	connectionGrid.put(connectionBackground,0,0);
	//Armo la box para la vinculacion
	serverLabel.set_label("Server IP:");
	serverAddress.set_max_length(15);
	serverButton.set_label("Connect");
	serverButton.signal_clicked().connect(sigc::mem_fun(*this,&ClientWindow::showLevelSelector));
	connectionContainer.set_spacing(8);
	connectionContainer.add(serverLabel);
	connectionContainer.add(serverAddress);
	connectionContainer.add(serverButton);
	connectionGrid.put(connectionContainer,0.2*width,0.65*height);
	//Agrego el boton de salida y el de creditos
	creditsButton.set_label("Credits");
	creditsButton.signal_clicked().connect(sigc::mem_fun(*this,&ClientWindow::showCredits));
	exitButton.set_label("Exit");
	exitButton.signal_clicked().connect(sigc::mem_fun(*this,&Gtk::Window::close));
	buttons.set_spacing(8);
	buttons.add(creditsButton);
	buttons.add(exitButton);
	connectionGrid.put(buttons,0.9*width,0.05*height);

	//Armo la pantalla de los creditos
	creditsGrid.set_name("creditsGrid");
	creditsBackground.setImage("../images/creditsbackground.jpg",width,height);
	creditsGrid.put(creditsBackground,0,0);
	credits.set_label("Creditos de prueba");
	creditsGrid.put(credits,0.4*width,0.4*height);
	backButton.set_label("Back");
	backButton.signal_clicked().connect(sigc::mem_fun(*this,&ClientWindow::showStart));
	creditsGrid.put(backButton,0.05*width,0.05*height);

	//Armo la pantalla de seleccion de niveles
	levelSelectorGrid.set_name("levelSelector");
	const int messagesWidth = width-height;
	messages.set_size_request(messagesWidth,height);
	messages.set_label("TEEEEST");
	//SparkMan
	sparkManIcon.setImage("../images/sparkMan.jpg",156,145);
	sparkManButton.set_image(sparkManIcon);
	sparkManButton.set_vexpand(true);
	sparkManButton.set_hexpand(true);
	//SnakeMan
	snakeManIcon.setImage("../images/snakeMan.jpg",156,145);
	snakeManButton.set_image(snakeManIcon);
	snakeManButton.set_vexpand(true);
	snakeManButton.set_hexpand(true);
	//NeedleMan
	needleManIcon.setImage("../images/needleMan.jpg",156,145);
	needleManButton.set_image(needleManIcon);
	needleManButton.set_vexpand(true);
	needleManButton.set_hexpand(true);
	//HardMan
	hardManIcon.setImage("../images/hardMan.jpg",156,145);
	hardManButton.set_image(hardManIcon);
	hardManButton.set_vexpand(true);
	hardManButton.set_hexpand(true);
	//MegaMan
	megaManIcon.setImage("../images/megaMan.jpg",156,145);
	megaManButton.set_image(megaManIcon);
	megaManButton.set_vexpand(true);
	megaManButton.set_hexpand(true);
	//TopMan
	topManIcon.setImage("../images/topMan.jpg",156,145);
	topManButton.set_image(topManIcon);
	topManButton.set_vexpand(true);
	topManButton.set_hexpand(true);
	//GeminiMan
	genimiManIcon.setImage("../images/geminiMan.jpg",156,145);
	geminiManButton.set_image(genimiManIcon);
	geminiManButton.set_vexpand(true);
	geminiManButton.set_hexpand(true);
	//MagnetMan
	magnetManIcon.setImage("../images/magnetMan.jpg",156,145);
	magnetManButton.set_image(magnetManIcon);
	magnetManButton.set_vexpand(true);
	magnetManButton.set_hexpand(true);
	//ShadowMan
	shadowManIcon.setImage("../images/shadowMan.jpg",156,145);
	shadowManButton.set_image(shadowManIcon);
	shadowManButton.set_vexpand(true);
	shadowManButton.set_hexpand(true);
	//Agrego los selectores a la grilla
	levelSelectorGrid.add(sparkManButton);
	levelSelectorGrid.attach_next_to(snakeManButton,sparkManButton,Gtk::PositionType::POS_RIGHT,1,1);
	levelSelectorGrid.attach_next_to(needleManButton,snakeManButton,Gtk::PositionType::POS_RIGHT,1,1);
	levelSelectorGrid.attach_next_to(hardManButton,sparkManButton,Gtk::PositionType::POS_BOTTOM,1,1);
	levelSelectorGrid.attach_next_to(megaManButton,hardManButton,Gtk::PositionType::POS_RIGHT,1,1);
	levelSelectorGrid.attach_next_to(topManButton,megaManButton,Gtk::PositionType::POS_RIGHT,1,1);
	levelSelectorGrid.attach_next_to(geminiManButton,hardManButton,Gtk::PositionType::POS_BOTTOM,1,1);
	levelSelectorGrid.attach_next_to(magnetManButton,geminiManButton,Gtk::PositionType::POS_RIGHT,1,1);
	levelSelectorGrid.attach_next_to(shadowManButton,magnetManButton,Gtk::PositionType::POS_RIGHT,1,1);
	levelSelectorGrid.attach_next_to(messages,sparkManButton,Gtk::PositionType::POS_LEFT,1,3);

	//Armo la pantalla usada para graficar el nivel
	//nivel.setImage("levelSelectorFacha.jpg",width,height);

	//Agrego las pantallas y activo la de coneccion
	selector.add(connectionGrid,"connectionGrid");
	selector.add(levelSelectorGrid,"levelSelector");
	//selector.add(nivel,"level");
	selector.add(creditsGrid,"creditsGrid");
	selector.set_visible_child("connectionGrid");

	show_all_children();
}

void ClientWindow::showStart() {
	selector.set_visible_child("connectionGrid");
}

void ClientWindow::showCredits() {
	selector.set_visible_child("creditsGrid");
}

void ClientWindow::showLevelSelector() {
	selector.set_visible_child("levelSelector");
}

void ClientWindow::showLevel() {
	selector.set_visible_child("level");
}

ClientWindow::~ClientWindow() {
}

