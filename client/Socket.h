/*
 * Socket.h
 *
 *  Created on: May 7, 2016
 *      Author: freddy
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <string>

#ifdef __cplusplus
extern "C" {
#endif
#include "cSocket.h"
#ifdef __cplusplus
}
#endif

class Socket {
private:
	socket_t socket;
	const std::string puerto;

public:
	Socket();

	//Crea un objeto socket desde un socket fd
	explicit Socket(const socket_t socket);

	//Creo un socket TCP hacia un servidor
	Socket(const std::string &ip, const std::string puerto);

	//Crea un socket TCP para ser servidor
	Socket(const std::string puerto, const int maxMappersQueue);

	//METODO BLOQUEANTE
	//Genera un socket vinculado a un cliente esperando conectarse
	Socket aceptarCliente();

	//Destrabo el socket bloqueado esperando un cliente y le envia un mensaje
	void destrabar(std::string mensaje);

	//Envia datos por el socket
	void enviar(const std::string &mensaje);
	void enviar(const int &mensaje);

	//Recibe datos hasta encontrar un caracter separador
	std::string recibirHasta(const char separador);

	void cerrar();

	virtual ~Socket();

private:
	//Convierte un numero de cualquier tipo a string (en decimal)
	template <typename T>
	std::string numeroATexto(T numero);
};

#endif /* SOCKET_H_ */
