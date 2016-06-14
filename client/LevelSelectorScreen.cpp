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

#include "../common/CommunicationCodes.h"

LevelSelectorScreen::LevelSelectorScreen(MegamanClientModel& model) :
	model(model) {
	const int width = Gdk::screen_width();
	const int height = Gdk::screen_height();
	const int imgWidth = width/3-50;	//-50 porque nos saca de fullscreen
	const int imgHeight = height/2-50;	//-50 porque nos saca de fullscreen

	//MegaMan
	dataLabel.set_label("");
	model.changeGameStatusSignal().connect(sigc::mem_fun(*this,&LevelSelectorScreen::fillText));
	exitButton.set_label("Disconnect from server");
	megamanContainer.add(dataLabel);
	megamanContainer.add(exitButton);
	//MagnetMan
	magnetManIcon.setImage("../sprites/level/bossImages/MagnetMan.png",imgWidth,imgHeight,false);
	magnetManIcon.set_vexpand(true);
	magnetManIcon.set_hexpand(true);
	magnetManButton.set_image(magnetManIcon);
	magnetManButton.set_relief(Gtk::RELIEF_NONE);
	magnetManButton.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(model,&MegamanClientModel::serverSendLevelSelected),MAGNETMAN));
	//SparkMan
	sparkManIcon.setImage("../sprites/level/bossImages/SparkMan.png",imgWidth,imgHeight,false);
	sparkManIcon.set_vexpand(true);
	sparkManIcon.set_hexpand(true);
	sparkManButton.set_image(sparkManIcon);
	sparkManButton.set_relief(Gtk::RELIEF_NONE);
	sparkManButton.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(model,&MegamanClientModel::serverSendLevelSelected),SPARKMAN));
	//RingMan
	ringManIcon.setImage("../sprites/level/bossImages/RingMan.png",imgWidth,imgHeight,false);
	ringManIcon.set_vexpand(true);
	ringManIcon.set_hexpand(true);
	ringManButton.set_image(ringManIcon);
	ringManButton.set_relief(Gtk::RELIEF_NONE);
	ringManButton.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(model,&MegamanClientModel::serverSendLevelSelected),RINGMAN));
	//FireMan
	fireManIcon.setImage("../sprites/level/bossImages/FireMan.png",imgWidth,imgHeight,false);
	fireManIcon.set_vexpand(true);
	fireManIcon.set_hexpand(true);
	fireManButton.set_image(fireManIcon);
	fireManButton.set_relief(Gtk::RELIEF_NONE);
	fireManButton.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(model,&MegamanClientModel::serverSendLevelSelected),FIREMAN));
	//BombMan
	bombManIcon.setImage("../sprites/level/bossImages/BombMan.png",imgWidth,imgHeight,false);
	bombManIcon.set_vexpand(true);
	bombManIcon.set_hexpand(true);
	bombManButton.set_image(bombManIcon);
	bombManButton.set_relief(Gtk::RELIEF_NONE);
	bombManButton.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(model,&MegamanClientModel::serverSendLevelSelected),BOMBMAN));

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

void LevelSelectorScreen::fillText() {
	std::string label = "\n";
	if ("1" == model.getClientNumer()) {
		label.append("You are the leader player\n");
		label.append("Select level to be played\n");
	} else {
		label.append("\nWait for player 1 to select level\n");
	}
	label.append(2,'\n');
	//MagnetMan
	label.append("MagnetMan: ");
	if (!model.getLevelStatus(MAGNETMAN)) label.append("not ");
	label.append("defeated\n");
	//SparkMan
	label.append("SparkMan: ");
	if (!model.getLevelStatus(SPARKMAN)) label.append("not ");
	label.append("defeated\n");
	//RingMan
	label.append("RingMan: ");
	if (!model.getLevelStatus(RINGMAN)) label.append("not ");
	label.append("defeated\n");
	//FireMan
	label.append("FireMan: ");
	if (!model.getLevelStatus(FIREMAN)) label.append("not ");
	label.append("defeated\n");
	//BombMan
	label.append("BombMan: ");
	if (!model.getLevelStatus(BOMBMAN)) label.append("not ");
	label.append("defeated\n");
	label.append(2,'\n');
	label.append("To disconnect and exit game press button below");
	label.append(2,'\n');
	dataLabel.set_label(label);
}

