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

typedef sigc::signal<void,std::string> StringSignal;

class MegamanClientModel : public Thread {
private:
	Socket* serverProxy;
	std::string clientNumber;
	std::map<int,bool> levelsStatus;
	Drawables drawables;
	SpriteDispenser sprites;
	bool recibirServer;
	StringSignal windowChangeSignal;
	StringSignal backgroundSignal;

public:
	MegamanClientModel();
	virtual ~MegamanClientModel();

	Drawables& getDrawables();
	void run();	//updateFromServer();

	StringSignal changeScreenSignal();
	StringSignal setBackgroundSignal();

	void connectServer(std::string ip, std::string port);
	std::string getClientNumer();
	void disconnectServer();

	void serverSendLevelSelected(int levelCode);
	void serverSendKeyboard(int keyboardState);
};

#endif /* SRC_MEGAMANCLIENTMODEL_H_ */
/*
#include <glibmm/main.h>
#include "Socket.h"
*/
