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
	const int imgWidth = width/4;
	const int imgHeight = height/3;
	set_homogeneous();

	//FIRST COLUMN
	//RingMan
	ringManIcon.setImage("../sprites/level/bossImages/RingMan.png",imgWidth,imgHeight,false);
	ringManButton.set_image(ringManIcon);
	ringManButton.set_relief(Gtk::RELIEF_NONE);
	ringManButton.set_vexpand(false);
	ringManButton.set_hexpand(false);
	ringManButton.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(model,&MegamanClientModel::serverSendLevelSelected),RINGMAN));
	firstColumn.add(ringManButton);
	//FireMan
	fireManIcon.setImage("../sprites/level/bossImages/FireMan.png",imgWidth,imgHeight,false);
	fireManButton.set_image(fireManIcon);
	fireManButton.set_relief(Gtk::RELIEF_NONE);
	fireManButton.set_vexpand(false);
	fireManButton.set_hexpand(false);
	fireManButton.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(model,&MegamanClientModel::serverSendLevelSelected),FIREMAN));
	firstColumn.add(fireManButton);
	add(firstColumn);

	//SECOND COLUMN
	//Header
	header.setImage("../sprites/level/background/header.png",imgWidth*4/3,imgHeight*0.5,false);
	header.set_vexpand(false);
	header.set_hexpand(true);
	secondColumn.add(header);
	instructionLabel.set_label("Select boss to fight!!!\n");
	secondColumn.add(instructionLabel);
	//MagnetMan
	magnetManIcon.setImage("../sprites/level/bossImages/MagnetMan.png",imgWidth,imgHeight,false);
	magnetManButton.set_image(magnetManIcon);
	magnetManButton.set_relief(Gtk::RELIEF_NONE);
	magnetManButton.set_vexpand(false);
	magnetManButton.set_hexpand(false);
	magnetManButton.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(model,&MegamanClientModel::serverSendLevelSelected),MAGNETMAN));
	secondColumn.add(magnetManButton);
	//Status box
	dataLabel.set_label("");
	secondColumn.add(dataLabel);
	secondColumn.add(players);
	model.changeGameStatusSignal().connect(sigc::mem_fun(*this,&LevelSelectorScreen::fillStatus));
	//Exit button
	exitButton.set_label("Disconnect from server");
	exitButton.set_vexpand(false);
	exitButton.set_hexpand(false);
	secondColumn.add(exitButton);
	add(secondColumn);

	//THIRD COLUMN
	//SparkMan
	sparkManIcon.setImage("../sprites/level/bossImages/SparkMan.png",imgWidth,imgHeight,false);
	sparkManButton.set_image(sparkManIcon);
	sparkManButton.set_relief(Gtk::RELIEF_NONE);
	sparkManButton.set_vexpand(false);
	sparkManButton.set_hexpand(false);
	sparkManButton.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(model,&MegamanClientModel::serverSendLevelSelected),SPARKMAN));
	thirdColumn.add(sparkManButton);
	//BombMan
	bombManIcon.setImage("../sprites/level/bossImages/BombMan.png",imgWidth,imgHeight,false);
	bombManButton.set_image(bombManIcon);
	bombManButton.set_relief(Gtk::RELIEF_NONE);
	bombManButton.set_vexpand(false);
	bombManButton.set_hexpand(false);
	bombManButton.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(model,&MegamanClientModel::serverSendLevelSelected),BOMBMAN));
	thirdColumn.add(bombManButton);
	add(thirdColumn);

	exitButton.grab_focus();
}

LevelSelectorScreen::~LevelSelectorScreen() {
	for (std::vector<Drawing*>::iterator it = playersAvatars.begin() ; it != playersAvatars.end(); ++it)
		delete (*it);
	playersAvatars.clear();
}

Gtk::Button& LevelSelectorScreen::getDisconnectButton() {
	return exitButton;
}

void LevelSelectorScreen::fillStatus() {
	const int width = Gdk::screen_width();
	const int height = Gdk::screen_height();
	const int imgWidth = width/4;
	const int imgHeight = height/3;

	//Escribo si es o no el leader player
	if ("1" == model.getClientNumber()) {
		dataLabel.set_label("You are leader player\nSelect a level\n");
	} else {
		dataLabel.set_label("Wait for leader player\nto select a level\n");
	}

	if (model.getLevelStatus(MAGNETMAN) && model.getLevelStatus(SPARKMAN) && model.getLevelStatus(RINGMAN)
			&& model.getLevelStatus(FIREMAN) && model.getLevelStatus(BOMBMAN))
		dataLabel.set_label("You defeated every enemy!!!\nCongratulations\n");

	//Pongo en gris los niveles ganados
	if (model.getLevelStatus(MAGNETMAN)) magnetManIcon.setImage("../sprites/level/bossImages/MagnetManDefeated.png",imgWidth,imgHeight,false);
	if (model.getLevelStatus(SPARKMAN)) sparkManIcon.setImage("../sprites/level/bossImages/SparkManDefeated.png",imgWidth,imgHeight,false);
	if (model.getLevelStatus(RINGMAN)) ringManIcon.setImage("../sprites/level/bossImages/RingManDefeated.png",imgWidth,imgHeight,false);
	if (model.getLevelStatus(FIREMAN)) fireManIcon.setImage("../sprites/level/bossImages/FireManDefeated.png",imgWidth,imgHeight,false);
	if (model.getLevelStatus(BOMBMAN)) bombManIcon.setImage("../sprites/level/bossImages/BombManDefeated.png",imgWidth,imgHeight,false);

	//Muestro megamanes segun cantidad de jugadores
	if (playersAvatars.size()!=(unsigned)model.getClientsConnected()) {
		for (std::vector<Drawing*>::iterator it = playersAvatars.begin() ; it != playersAvatars.end(); ++it)
			delete (*it);
		playersAvatars.clear();
	}
	for (int i = playersAvatars.size(); i < model.getClientsConnected(); ++i) {
		Drawing* player = new Drawing;
		std::string ruta = "../sprites/megaman pc";
		ruta.append(std::to_string(i+1));
		ruta.append("/megaman_idle.png");
		player->setImage(ruta,imgWidth/4,imgWidth/4,false);
		players.add(*player);
		playersAvatars.push_back(player);
		player->show();
	}
}

