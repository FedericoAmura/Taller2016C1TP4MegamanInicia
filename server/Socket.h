/*
 * Socket.h
 *
 *  Created on: Apr 18, 2016
 *      Author: nicolas
 */

#ifndef SERVER_SOCKET_H_
#define SERVER_SOCKET_H_

#include <stdint.h>

#include "Observer.h"
#include "SendRecvThread.h"

/*version concurrente de client socket*/
class Socket :public Observer{
	friend class SendThread;
	friend class RecvThread;

	Observer* modelo;
	SendThread sendThr;
	RecvThread recvThr;
	bool comunicandose;
	Mutex abiertoMutex;
	bool abierto;
	bool send(char* data,int largo);
	bool recieve(char* data,int largo);
	bool estaAbierto();
	void shutdown();

public:
	explicit Socket(Observer* modelo);
	Socket(int descriptor,Observer* modelo);
	virtual ~Socket();
	void iniciarComunicaciones();

	void enviar(char* mensaje);
	virtual void notify(Event* e);

protected:
	int descriptor;
};

#endif /* SERVER_SOCKET_H_ */
