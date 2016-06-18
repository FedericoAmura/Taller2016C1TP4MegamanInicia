/*
 * MegamanClientModel.h
 *
 *  Created on: May 18, 2016
 *      Author: freddy
 */

#ifndef SRC_MEGAMANCLIENTMODEL_H_
#define SRC_MEGAMANCLIENTMODEL_H_

#include <cstdbool>
#include <string>

#include "Socket.h"
#include "Drawable.h"
#include "Drawables.h"
#include "../common/Drawing.h"
#include "../common/Thread.h"
#include "../common/SpriteDispenser.h"

typedef unsigned int uint;
typedef sigc::signal<void> Signal;
typedef sigc::signal<void,std::string> StringSignal;

class MegamanClientModel : public Thread {
private:
	Socket* serverProxy;
	std::string clientNumber;
	int clientsConnected;
	std::map<int,bool> levelsStatus;
	Drawables drawables;
	uint clientsDrawed;
	sigc::connection cicleDrawablesConn;
	SpriteDispenser sprites;
	bool recibirServer;
	Signal gameStatusChangeSignal;
	StringSignal windowChangeSignal;

public:
	MegamanClientModel();
	virtual ~MegamanClientModel();

	Drawables& getDrawables();
	void run();	//updateFromServer();

	Signal changeGameStatusSignal();
	StringSignal changeScreenSignal();

	void connectServer(std::string ip, std::string port);
	std::string getClientNumber();
	int getClientsConnected();
	bool getLevelStatus(int idLevel);
	void disconnectServer();
	bool cicleDrawables();

	void serverSendLevelSelected(int levelCode);
	void serverSendKeyboard(int keyboardState);

private:
	bool backToLevelSelectionSignal();
};

#endif /* SRC_MEGAMANCLIENTMODEL_H_ */
/*
#include <glibmm/main.h>
#include "Socket.h"
*/
