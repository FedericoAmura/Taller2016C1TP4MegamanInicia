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

	//MegaMan
	dataLabel.set_label("");
	dataLabel.signal_realize().connect(sigc::mem_fun(*this,&LevelSelectorScreen::fillText));
	exitButton.set_label("Disconnect from server");
	megamanContainer.add(dataLabel);
	megamanContainer.add(exitButton);
	//MagnetMan
	magnetManIcon.setImage("../sprites/level/bossImages/MagnetMan.png",imgWidth,imgHeight,false);
	magnetManIcon.set_vexpand(true);
	magnetManIcon.set_hexpand(true);
	magnetManButton.set_image(magnetManIcon);
	magnetManButton.set_relief(Gtk::RELIEF_NONE);
	//SparkMan
	sparkManIcon.setImage("../sprites/level/bossImages/SparkMan.png",imgWidth,imgHeight,false);
	sparkManIcon.set_vexpand(true);
	sparkManIcon.set_hexpand(true);
	sparkManButton.set_image(sparkManIcon);
	sparkManButton.set_relief(Gtk::RELIEF_NONE);
	//RingMan
	ringManIcon.setImage("../sprites/level/bossImages/RingMan.png",imgWidth,imgHeight,false);
	ringManIcon.set_vexpand(true);
	ringManIcon.set_hexpand(true);
	ringManButton.set_image(ringManIcon);
	ringManButton.set_relief(Gtk::RELIEF_NONE);
	//FireMan
	fireManIcon.setImage("../sprites/level/bossImages/FireMan.png",imgWidth,imgHeight,false);
	fireManIcon.set_vexpand(true);
	fireManIcon.set_hexpand(true);
	fireManButton.set_image(fireManIcon);
	fireManButton.set_relief(Gtk::RELIEF_NONE);
	//BombMan
	bombManIcon.setImage("../sprites/level/bossImages/BombMan.png",imgWidth,imgHeight,false);
	bombManIcon.set_vexpand(true);
	bombManIcon.set_hexpand(true);
	bombManButton.set_image(bombManIcon);
	bombManButton.set_relief(Gtk::RELIEF_NONE);

	//Agrego los selectores a la grilla
	add(fireManButton);
	attach_next_to(magnetManButton,fireManButton,Gtk::PositionType::POS_RIGHT,1,1);
	attach_next_to(sparkManButton,magnetManButton,Gtk::PositionType::POS_RIGHT,1,1);
	attach_next_to(ringManButton,fireManButton,Gtk::PositionType::POS_BOTTOM,1,1);
	attach_next_to(bombManButton,sparkManButton,Gtk::PositionType::POS_BOTTOM,1,1);
	attach_next_to(megamanContainer,magnetManButton,Gtk::PositionType::POS_BOTTOM,1,1);
}

LevelSelectorScreen::~LevelSelectorScreen() {
}

Gtk::Button& LevelSelectorScreen::getDisconnectButton() {
	return exitButton;
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

void LevelSelectorScreen::fillText() {
	std::string label = "\n";
	label.append("You are player "+model.getClientNumer()+"\n");
	if ("1" == model.getClientNumer())
		label.append("Select level to be played\n");
	else label.append("Wait for player 1 to select level\n");
	label.append(2,'\n');
	label.append("MagnetMan: not defeated\n");
	label.append("SparkMan: not defeated\n");
	label.append("RingMan: not defeated\n");
	label.append("FireMan: not defeated\n");
	label.append("BombMan: not defeated\n");
	label.append(2,'\n');
	label.append("To disconnect and exit game press button below");
	label.append(2,'\n');
	dataLabel.set_label(label);
}

