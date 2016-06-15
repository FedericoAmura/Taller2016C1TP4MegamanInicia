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

	/* TODO
	 * pasar a 3 vbox con los niveles
	 * que la del medio sea cartel megaman, nivel, status, boton salir chico
	 * en status puedo poner megamanes de colores
	 *
	 *mensajes de READY, GANASTE PERDISTE O COSAS ASI
	 *https://cooltext.com/Logo-Design-Gunmetal
	 *
	 * hacer que los drawables de megamanes se pongan con un segun caigan, se dibujen con colores segun eso
	 * que caga tanto caminen o den pasos
	 *
	 * dividir levelscreen en 3 fixed
	 * -background (fondo)
	 * -middle (cosas del nivel)
	 * -foreground (megamanes, vida y enemigos)
	 */

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
	dataLabel.set_label("You are leader player\n");
	secondColumn.add(dataLabel);
	megaman1.setImage("../sprites/megaman pc/megaman_idle.png",imgWidth/4,imgWidth/4,false);
	megaman2.setImage("../sprites/megaman pc/megaman_idle.png",imgWidth/4,imgWidth/4,false);
	players.add(megaman1);
	players.add(megaman2);
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
}

Gtk::Button& LevelSelectorScreen::getDisconnectButton() {
	return exitButton;
}

void LevelSelectorScreen::fillStatus() {
//	std::string label = "\n";
//	if ("1" == model.getClientNumer()) {
//		label.append("You are the leader player\n");
//		label.append("Select level to be played\n");
//	} else {
//		label.append("\nWait for player 1 to select level\n");
//	}
//	label.append(2,'\n');
//	//MagnetMan
//	label.append("MagnetMan: ");
//	if (!model.getLevelStatus(MAGNETMAN)) label.append("not ");
//	label.append("defeated\n");
//	//SparkMan
//	label.append("SparkMan: ");
//	if (!model.getLevelStatus(SPARKMAN)) label.append("not ");
//	label.append("defeated\n");
//	//RingMan
//	label.append("RingMan: ");
//	if (!model.getLevelStatus(RINGMAN)) label.append("not ");
//	label.append("defeated\n");
//	//FireMan
//	label.append("FireMan: ");
//	if (!model.getLevelStatus(FIREMAN)) label.append("not ");
//	label.append("defeated\n");
//	//BombMan
//	label.append("BombMan: ");
//	if (!model.getLevelStatus(BOMBMAN)) label.append("not ");
//	label.append("defeated\n");
//	label.append(2,'\n');
//	label.append("To disconnect and exit game press button below");
//	label.append(2,'\n');
//	dataLabel.set_label(label);
}

