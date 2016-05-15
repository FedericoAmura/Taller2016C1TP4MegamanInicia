/*
 * Thread.cpp
 *
 *  Created on: Apr 3, 2016
 *      Author: freddy
 */

#include "Thread.h"

Thread::Thread() {}

void Thread::start() {
	pthread_create(&thread, NULL, Thread::runner, this);
}

void Thread::join() {
    pthread_join(thread, NULL);
}

Thread::~Thread() {}

