/*
 * Stat.h
 *
 *  Created on: May 31, 2016
 *      Author: nicolas
 */

#ifndef SERVER_MODEL_STAT_H_
#define SERVER_MODEL_STAT_H_

/*type t must be a number, or implement +=, -=, =,and >.
 * must also be able to handle >0 and =0*/
template<class T>
class Stat{
	const T max;
	T current;
public:
	Stat(T max):max(max),current(max){}
	Stat(T max,T initial):max(max),current(0){
		inc(initial);
	}
	virtual ~Stat(){}
	void maxOut(){
		current=max;
	}
	void inc(T amount){
		current+=amount;
		if(current>max)
			current=max;
	}
	void dec(T amount){
		current-=amount;
		if(current<0)
			current=0;
	}
	T getCurrent(){
		return current;
	}
};

#endif /* SERVER_MODEL_STAT_H_ */
