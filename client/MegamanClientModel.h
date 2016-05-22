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
#include "MyArea.h"
#include "Thread.h"

class MegamanClientModel : public Thread {
private:
	Socket* serverProxy;
	Drawables drawables;
	bool recibirServer;

public:
	MegamanClientModel();
	virtual ~MegamanClientModel();

	Drawables& getDrawables();
	void run();	//updateFromServer();

	void connectServer(std::string ip, std::string port);
	void disconnectServer();

	void serverSendKey(int keyCode);
};

#endif /* SRC_MEGAMANCLIENTMODEL_H_ */
/*
#include <glibmm/main.h>
#include "Socket.h"
*/
