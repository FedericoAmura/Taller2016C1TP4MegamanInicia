/*
 * server_Juego1.h
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#ifndef SERVER_JUEGO_H_
#define SERVER_JUEGO_H_

#include <queue>

#include <map>
#include <string>

#include "Evento.h"
#include "HandlerCoordinator.h"
#include "Observador.h"
#include "Socket.h"
#include "Thread.h"
class Server;//forward declaration


class Juego:public Thread,public Observador{
	Mutex continuarMutex;
	bool continuar;
	Server* server;
	Mutex queueMutex;
	std::queue<Evento*> eventQueue;
	HandlerCoordinator manager;

	/*candidato a extraer*/
	Mutex clientesMutex;
	std::map<int,Socket*> clientes;
public:
	explicit Juego(Server* server);
	virtual ~Juego();
	virtual void run();
	void notificar(Evento* e);
	void cerrar();

	void aniadirCliente(int descriptor);
	void enviarA(std::string data, int destino);
private:
	bool seguirCorriendo();
};

#endif /* SERVER_JUEGO_H_ */
