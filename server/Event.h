/*
 * common_Evento.h
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#ifndef SERVER_EVENT_H_
#define SERVER_EVENT_H_

#include <string>

/*clase abstracta*/
class Event {
public:
	Event();
	virtual ~Event();
	int getId();

protected:
	int id;
};

/****************************************************/
class NewConnection:public Event {
	int descriptor;

public:
	explicit NewConnection(int descriptor);
	virtual ~NewConnection();
	int getDescriptor();
};

/****************************************************/
class MessageRecieved:public Event {
	std::string data;
	int receptor;

public:
	MessageRecieved(std::string data,int receptor);
	virtual ~MessageRecieved();
	std::string getMessage();
	int getReceptor();
};

/****************************************************/
class MessageSent:public Event {
	std::string data;
	int destination;

public:
	MessageSent(std::string data,int destino);
	virtual ~MessageSent();
	std::string getMessage();
	int getDestination();
};

/******************************************************/
class ConnectionEnded: public Event{
	int descriptor;

public:
	explicit ConnectionEnded(int client);
	virtual ~ConnectionEnded();
	int getClient();
};

/*************************************************************/
#define EXIT 0
#define LOST -1
#define WON 1

class LevelFinished: public Event{
	int condition;
	int levelId;
public:
	explicit LevelFinished(int condition, int id);
	virtual ~LevelFinished();
	int getCondition();
	int getLevelId();
};
#endif /* SERVER_EVENT_H_ */
