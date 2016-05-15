/*
 * Thread.h
 *
 *  Created on: Apr 3, 2016
 *      Author: freddy
 */

#ifndef SERVER_THREAD_H_
#define SERVER_THREAD_H_

#include <pthread.h>

class Thread {
private:
	pthread_t thread;

	static void *runner(void *data){
        Thread *self = (Thread*)data;
        self->run();
        return NULL;
    }

public:
	Thread();

	//Arranca el thread
	void start();

	//Joinea el llamador al thread
	void join();

	//Metodo de los hijos a correr en un nuevo thread
	virtual void run() = 0;

	virtual ~Thread();
};

#endif /* SERVER_THREAD_H_ */
