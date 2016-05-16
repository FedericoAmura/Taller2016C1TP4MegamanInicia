/*
 * server_Juego1.h
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#ifndef COMMON_COMMON_JUEGO_H_
#define COMMON_COMMON_JUEGO_H_

#include <queue>

#include <map>
#include <string>

#include "../common/common_Evento.h"
#include "../common/common_HandlerCoordinator.h"
#include "../common/common_Observador.h"
#include "../common/common_Socket.h"
#include "../common/common_Thread.h"
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

#endif /* COMMON_COMMON_JUEGO_H_ */
