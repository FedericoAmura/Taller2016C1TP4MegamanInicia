/*
 * Threads.cpp
 *
 *  Created on: Apr 11, 2016
 *      Author: nicolas
 */

#include "../common/common_Thread.h"

#include <pthread.h>
#include <stdexcept>



void* Thread::runner(void *data) {
	Thread *self = (Thread*)data;
	self->run();
	return 0;
}


Thread::Thread() {
	thread=0;
}

void Thread::start() {
	if(pthread_create(&thread, NULL, Thread::runner, this)!=0)
		throw std::runtime_error("Error: creacion thread");
}

void Thread::join() {
	pthread_join(thread, NULL);
}

/****************************Mutex****************************/
Mutex::Mutex() {
	pthread_mutex_init(&this->mutex, NULL);
}

void Mutex::lock() {
	pthread_mutex_lock(&this->mutex);
}

void Mutex::unlock() {
	pthread_mutex_unlock(&this->mutex);
}

Mutex::~Mutex() {
	pthread_mutex_destroy(&this->mutex);
}

/****************************Lock****************************/
Lock::Lock(Mutex &m) : m(m) {
	m.lock();
}

Lock::~Lock() {
	m.unlock();
}

