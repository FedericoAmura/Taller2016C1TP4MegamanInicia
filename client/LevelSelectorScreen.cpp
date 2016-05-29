/*
 * LevelSelectorScreen.cpp
 *
 *  Created on: May 15, 2016
 *      Author: freddy
 */

#include "LevelSelectorScreen.h"

#include <gdkmm/general.h>
#include <gtkmm/enums.h>
#include <iostream>

LevelSelectorScreen::LevelSelectorScreen(MegamanClientModel& model) :
	model(model) {
	const int width = Gdk::screen_width();
	const int height = Gdk::screen_height();
	const int imgWidth = width/3-50;	//-50 porque nos saca de fullscreen
	const int imgHeight = height/2-50;	//-50 porque nos saca de fullscreen

	const int messagesWidth = width-height;
	//messages.set_size_request(messagesWidth,height);
	//messages.set_label("Elija un nivel\nAca escribimos cosas como los jugadores conectados");

	//MegaMan
	megaManIcon.setImage("../images/levelImages/MegaMan.png",imgWidth,imgHeight,false);
	megaManIcon.set_vexpand(true);
	megaManIcon.set_hexpand(true);
	megaManButton.set_image(megaManIcon);
	//MagnetMan
	magnetManIcon.setImage("../images/levelImages/MagnetMan.png",imgWidth,imgHeight,false);
	magnetManIcon.set_vexpand(true);
	magnetManIcon.set_hexpand(true);
	magnetManButton.set_image(magnetManIcon);
	//SparkMan
	sparkManIcon.setImage("../images/levelImages/SparkMan.jpg",imgWidth,imgHeight,false);
	sparkManIcon.set_vexpand(true);
	sparkManIcon.set_hexpand(true);
	sparkManButton.set_image(sparkManIcon);
	//RingMan
	ringManIcon.setImage("../images/levelImages/RingMan.png",imgWidth,imgHeight,false);
	ringManIcon.set_vexpand(true);
	ringManIcon.set_hexpand(true);
	ringManButton.set_image(ringManIcon);
	//FireMan
	fireManIcon.setImage("../images/levelImages/FireMan.png",imgWidth,imgHeight,false);
	fireManIcon.set_vexpand(true);
	fireManIcon.set_hexpand(true);
	fireManButton.set_image(fireManIcon);
	//BombMan
	bombManIcon.setImage("../images/levelImages/BombMan.png",imgWidth,imgHeight,false);
	bombManIcon.set_vexpand(true);
	bombManIcon.set_hexpand(true);
	bombManButton.set_image(bombManIcon);

	//Agrego los selectores a la grilla
	add(megaManButton);
	attach_next_to(magnetManButton,megaManButton,Gtk::PositionType::POS_RIGHT,1,1);
	attach_next_to(sparkManButton,magnetManButton,Gtk::PositionType::POS_RIGHT,1,1);
	attach_next_to(ringManButton,megaManButton,Gtk::PositionType::POS_BOTTOM,1,1);
	attach_next_to(fireManButton,ringManButton,Gtk::PositionType::POS_RIGHT,1,1);
	attach_next_to(bombManButton,fireManButton,Gtk::PositionType::POS_RIGHT,1,1);
}

Gtk::Button& LevelSelectorScreen::getMegamanButton() {
	return megaManButton;
}

Gtk::Button& LevelSelectorScreen::getMagnetManButton() {
	return magnetManButton;
}

Gtk::Button& LevelSelectorScreen::getSparkManButton() {
	return sparkManButton;
}

Gtk::Button& LevelSelectorScreen::getRingManButton() {
	return ringManButton;
}

Gtk::Button& LevelSelectorScreen::getFireManButton() {
	return fireManButton;
}

Gtk::Button& LevelSelectorScreen::getBombManButton() {
	return bombManButton;
}

LevelSelectorScreen::~LevelSelectorScreen() {
}

