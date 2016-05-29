/*
 * MyContactListener.h
 *
 *  Created on: May 29, 2016
 *      Author: nicolas
 */

#ifndef SERVER_MODEL_MYCONTACTLISTENER_H_
#define SERVER_MODEL_MYCONTACTLISTENER_H_

#include <Box2D/Box2D.h>

class MyContactListener: public b2ContactListener {
	void setJump(b2Fixture* fixture,bool state);
	void setAllJumps(b2Contact* contact,bool state);

public:
	MyContactListener();
	virtual ~MyContactListener();
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};

#endif /* SERVER_MODEL_MYCONTACTLISTENER_H_ */
