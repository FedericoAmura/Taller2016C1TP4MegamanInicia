/*
 * common_Observador.h
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#ifndef SERVER_OBSERVADOR_H_
#define SERVER_OBSERVADOR_H_

#include "Evento.h"

class Observador {
public:
	Observador();
	virtual ~Observador();
	virtual void notificar(Evento* e)=0;
};

#endif /* SERVER_OBSERVADOR_H_ */
