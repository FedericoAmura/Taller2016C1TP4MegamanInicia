/*
 * Lock.h
 *
 *  Created on: Apr 3, 2016
 *      Author: freddy
 */

#ifndef SERVER_LOCK_H_
#define SERVER_LOCK_H_

#include "Mutex.h"

//clase para manejo automatico (por RAII) de un mutex
class Lock {
private:
	Mutex &m;

public:
	explicit Lock(Mutex &m);
	~Lock();

private:
	Lock(const Lock&);
	Lock& operator=(const Lock&);
};

#endif /* SERVER_LOCK_H_ */
