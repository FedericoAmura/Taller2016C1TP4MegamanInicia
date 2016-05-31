/*
 * common_SendThread.h
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#ifndef SERVER_SENDRECVTHREAD_H_
#define SERVER_SENDRECVTHREAD_H_

#include <string>

#include "Observer.h"
#include "Thread.h"
#include "ThreadQueue.h"

class Socket;//forward declaration

class SendThread: public Thread {
	Socket* socket;
	ThreadQueue<std::string> aEnviar;

public:
	explicit SendThread(Socket* s);
	virtual ~SendThread();
	virtual void run();
	void enviar(std::string  data);
};

class RecvThread: public Thread {
	Socket* socket;
	Observer* observador;

public:
	RecvThread(Socket* s, Observer* o);
	virtual ~RecvThread();
	virtual void run();
};
#endif /* SERVER_SENDRECVTHREAD_H_ */
