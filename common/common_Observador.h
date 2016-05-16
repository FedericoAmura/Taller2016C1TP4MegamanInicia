/*
 * common_Observador.h
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#ifndef COMMON_COMMON_OBSERVADOR_H_
#define COMMON_COMMON_OBSERVADOR_H_

#include "../common/common_Evento.h"

class Observador {
public:
	Observador();
	virtual ~Observador();
	virtual void notificar(Evento* e)=0;
};

#endif /* COMMON_COMMON_OBSERVADOR_H_ */
