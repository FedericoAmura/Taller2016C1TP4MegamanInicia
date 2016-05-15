/*
 * common_Socket.cpp
 *
 *  Created on: May 7, 2016
 *      Author: freddy
 */

#include <string>

#include "Socket.h"

Socket::Socket(socket_t socket)
	: socket(socket) {
}

Socket::Socket(const std::string &ip, const std::string puerto)
	: puerto(puerto) {
	if (0 != socket_init_client(&socket, puerto.c_str(), ip.c_str())) {
		throw std::exception();
	}
}


Socket::Socket(const std::string puerto, const int maxMappersQueue)
	: puerto(puerto) {
	if (0 != socket_init_server(&socket, puerto.c_str())) {
		throw std::exception();
	}
	if (0 != socket_listen(&socket, maxMappersQueue)) {
		throw std::exception();
	}
}

Socket Socket::aceptarCliente() {
	socket_t clienteSkt;
	if (0 != socket_accept(&socket,&clienteSkt)) {
		throw std::exception();
	}
	Socket clienteSKT(clienteSkt);
	return clienteSKT;
}

void Socket::destrabar(std::string mensaje) {
	Socket destrabador("127.0.0.1",puerto);
	destrabador.enviar(mensaje);
	destrabador.cerrar();
}

void Socket::enviar(const std::string &mensaje){
	if (0 != socket_send(&socket, mensaje.c_str(), mensaje.length())) {
		throw std::exception();
	}
}

std::string Socket::recibirHasta(const char separador){
	std::string linea;
	char letter = '\n';
	while (0 == socket_receive(&socket,&letter,1)) {
		if (letter == separador) break;
		linea += letter;
	}
	return linea;
}

void Socket::cerrar() {
	socket_shutdown(&socket);
	socket_destroy(&socket);
}

Socket::~Socket() {
}

