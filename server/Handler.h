/*
 * common_Handler.h
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#ifndef SERVER_HANDLER_H_
#define SERVER_HANDLER_H_

#include "Event.h"

class Game;//forward declaration

/*clase abstracta, deben ser functors*/
class Handler {
public:
	explicit Handler(Game* j);
	virtual ~Handler();
	virtual void handle(Event* e)=0;

protected:
	Game* game;
};

/*************************************************/
class AcceptConnection: public Handler{
public:
	explicit AcceptConnection(Game* j);
	virtual ~AcceptConnection();
	void handle(Event* e);
};

/*************************************************/
class RecvMessage: public Handler{
public:
	explicit RecvMessage(Game* j);
	virtual ~RecvMessage();
	void handle(Event* e);
};

/*************************************************/
class SendMessage: public Handler{
public:
	explicit SendMessage(Game* j);
	virtual ~SendMessage();
	void handle(Event* e);
};

/************************************************/
class DisconnectClient: public Handler{
public:
	explicit DisconnectClient(Game* j);
	virtual ~DisconnectClient();
	void handle(Event* e);
};

/************************************************/
class FinishLevel: public Handler{
public:
	explicit FinishLevel(Game* j);
	virtual ~FinishLevel();
	void handle(Event* e);
};
#endif /* SERVER_HANDLER_H_ */
