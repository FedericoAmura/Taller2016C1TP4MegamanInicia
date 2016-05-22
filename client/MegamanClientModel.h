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
#include <glibmm/main.h>

#include "Socket.h"
#include "Drawable.h"
#include "Drawables.h"
#include "MyArea.h"

class MegamanClientModel {
private:
	sigc::connection serverReceiver;
	Socket* serverProxy;
	Drawables drawables;

public:
	MegamanClientModel();
	virtual ~MegamanClientModel();

	Drawables& getDrawables();
	bool updateDrawables();

	void connectServer(std::string ip, std::string port);
	void disconnectServer();

	void serverSendKey(int keyCode);
};

#endif /* SRC_MEGAMANCLIENTMODEL_H_ */
/*
#include <glibmm/main.h>
#include "Socket.h"
*/
