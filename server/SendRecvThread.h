/*
 * common_SendThread.h
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#ifndef SERVER_SENDRECVTHREAD_H_
#define SERVER_SENDRECVTHREAD_H_

#include <queue>
#include <string>
#include "Observador.h"
#include "../server/Thread.h"

class Socket;//forward declaration

class SendThread: public Thread {
	Socket* socket;
	std::queue<std::string> aEnviar;

public:
	explicit SendThread(Socket* s);
	virtual ~SendThread();
	virtual void run();
	void enviar(char* data);
};

class RecvThread: public Thread {
	Socket* socket;
	Observador* observador;

public:
	RecvThread(Socket* s, Observador* o);
	virtual ~RecvThread();
	virtual void run();
};
#endif /* SERVER_SENDRECVTHREAD_H_ */
