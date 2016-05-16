/*
 * common_Evento.h
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#ifndef COMMON_COMMON_EVENTO_H_
#define COMMON_COMMON_EVENTO_H_

#include <string>

/*clase abstracta*/
class Evento {
public:
	Evento();
	virtual ~Evento();
	int getId();

protected:
	int id;
};

/****************************************************/
class NuevaConeccion:public Evento {
	int descriptor;

public:
	explicit NuevaConeccion(int descriptor);
	virtual ~NuevaConeccion();
	int getDescriptor();
};

/****************************************************/
class MensajeRecibido:public Evento {
	std::string data;
	int receptor;

public:
	explicit MensajeRecibido(std::string data,int receptor);
	virtual ~MensajeRecibido();
	std::string getMensaje();
	int getReceptor();
};

/****************************************************/
class EnvioMensaje:public Evento {
	std::string data;
	int destino;

public:
	explicit EnvioMensaje(std::string data,int destino);
	virtual ~EnvioMensaje();
	std::string getMensaje();
	int getDestino();
};
#endif /* COMMON_COMMON_EVENTO_H_ */
