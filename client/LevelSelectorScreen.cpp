/*
 * LevelSelectorScreen.cpp
 *
 *  Created on: May 15, 2016
 *      Author: freddy
 */

#include "LevelSelectorScreen.h"

#include <gdkmm/general.h>
#include <gtkmm/enums.h>

LevelSelectorScreen::LevelSelectorScreen() {
	const int width = Gdk::screen_width();
	const int height = Gdk::screen_height();

	const int messagesWidth = width-height;
	messages.set_size_request(messagesWidth,height);
	messages.set_label("Elija un nivel\nAca escribimos cosas como los jugadores conectados");
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
	add(sparkManButton);
	attach_next_to(snakeManButton,sparkManButton,Gtk::PositionType::POS_RIGHT,1,1);
	attach_next_to(needleManButton,snakeManButton,Gtk::PositionType::POS_RIGHT,1,1);
	attach_next_to(hardManButton,sparkManButton,Gtk::PositionType::POS_BOTTOM,1,1);
	attach_next_to(megaManButton,hardManButton,Gtk::PositionType::POS_RIGHT,1,1);
	attach_next_to(topManButton,megaManButton,Gtk::PositionType::POS_RIGHT,1,1);
	attach_next_to(geminiManButton,hardManButton,Gtk::PositionType::POS_BOTTOM,1,1);
	attach_next_to(magnetManButton,geminiManButton,Gtk::PositionType::POS_RIGHT,1,1);
	attach_next_to(shadowManButton,magnetManButton,Gtk::PositionType::POS_RIGHT,1,1);
	attach_next_to(messages,sparkManButton,Gtk::PositionType::POS_LEFT,1,3);
}

Gtk::Button& LevelSelectorScreen::getMegamanButton() {
	return megaManButton;
}

LevelSelectorScreen::~LevelSelectorScreen() {
}

