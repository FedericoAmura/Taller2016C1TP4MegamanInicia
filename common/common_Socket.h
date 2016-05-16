/*
 * Socket.h
 *
 *  Created on: Apr 18, 2016
 *      Author: nicolas
 */

#ifndef COMMON_COMMON_SOCKET_H_
#define COMMON_COMMON_SOCKET_H_

#include <stdint.h>

#include "../common/common_Observador.h"
#include "../common/common_SendRecvThread.h"

/*version concurrente de client socket*/
class Socket :public Observador{
	friend class SendThread;
	friend class RecvThread;

	Observador* modelo;
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
	explicit Socket(Observador* modelo);
	Socket(int descriptor,Observador* modelo);
	virtual ~Socket();
	void iniciarComunicaciones();

	void enviar(char* mensaje);
	virtual void notificar(Evento* e);

protected:
	int descriptor;
};

#endif /* COMMON_COMMON_SOCKET_H_ */
