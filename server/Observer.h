/*
 * common_Observador.h
 *
 *  Created on: May 10, 2016
 *      Author: nicolas
 */

#ifndef SERVER_OBSERVER_H_
#define SERVER_OBSERVER_H_

#include "Event.h"

class Observer {
public:
	Observer();
	virtual ~Observer();
	virtual void notify(Event* e)=0;
};

#endif /* SERVER_OBSERVER_H_ */
