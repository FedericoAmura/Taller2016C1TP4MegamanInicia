/*
 * ThreadQueue.h
 *
 *  Created on: May 27, 2016
 *      Author: nicolas
 */

#ifndef SERVER_THREADQUEUE_H_
#define SERVER_THREADQUEUE_H_

#include <queue>
#include <pthread.h>

template <typename T> class ThreadQueue {
	std::queue<T>   m_queue;
	pthread_mutex_t m_mutex;
	pthread_cond_t  m_condv;

public:
	ThreadQueue(){
		pthread_mutex_init(&m_mutex, NULL);
		pthread_cond_init(&m_condv, NULL);
	}

	/*frees the resources necesary for queue to work
	 * does not free resource of queue contents*/
	virtual ~ThreadQueue(){
		pthread_mutex_destroy(&m_mutex);
		pthread_cond_destroy(&m_condv);
	}

	/*adds item to queue*/
	void push(T item){
		pthread_mutex_lock(&m_mutex);
		m_queue.push(item);
		pthread_cond_signal(&m_condv);
		pthread_mutex_unlock(&m_mutex);
	}

	/*removes and returns element at front of queue
	 * if there's no element it waits until there's one*/
	T pop(){
		pthread_mutex_lock(&m_mutex);
		while (m_queue.size() == 0) {
			pthread_cond_wait(&m_condv, &m_mutex);
		}
		T item = m_queue.front();
		m_queue.pop();
		pthread_mutex_unlock(&m_mutex);
		return item;
	}

	/*returns number of elements in queue*/
	int size() {
		pthread_mutex_lock(&m_mutex);
		int size = m_queue.size();
		pthread_mutex_unlock(&m_mutex);
		return size;
	}

	/*returns true if queue empty*/
	bool empty(){
		pthread_mutex_lock(&m_mutex);
		bool isEmpty = m_queue.empty();
		pthread_mutex_unlock(&m_mutex);
		return isEmpty;
	}
};

#endif /* SERVER_THREADQUEUE_H_ */
