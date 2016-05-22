/*
 * Mutex.cpp
 *
 *  Created on: Apr 3, 2016
 *      Author: freddy
 */

#include "Mutex.h"

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

