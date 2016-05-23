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
	explicit MessageRecieved(std::string data,int receptor);
	virtual ~MessageRecieved();
	std::string getMessage();
	int getReceptor();
};

/****************************************************/
class MessageSent:public Event {
	std::string data;
	int destination;

public:
	explicit MessageSent(std::string data,int destino);
	virtual ~MessageSent();
	std::string getMessage();
	int getDestination();
};
#endif /* SERVER_EVENT_H_ */
