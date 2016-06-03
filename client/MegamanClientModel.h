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
	Drawables drawables;
	SpriteDispenser sprites;
	bool recibirServer;
	StringSignal windowChangeSignal;

public:
	MegamanClientModel();
	virtual ~MegamanClientModel();

	Drawables& getDrawables();
	void run();	//updateFromServer();

	StringSignal changeScreenSignal();

	void connectServer(std::string ip, std::string port);
	void disconnectServer();

	void serverSendLevelSelected(int levelCode);
	void serverSendKey(int keyCode);
};

#endif /* SRC_MEGAMANCLIENTMODEL_H_ */
/*
#include <glibmm/main.h>
#include "Socket.h"
*/
