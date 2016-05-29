/*
 * MyContactListener.cpp
 *
 *  Created on: May 29, 2016
 *      Author: nicolas
 */

#include "MyContactListener.h"
#include "Megaman.h"
#include "LevelObject.h"

MyContactListener::MyContactListener() {
	// TODO Auto-generated constructor stub

}

MyContactListener::~MyContactListener() {
	// TODO Auto-generated destructor stub
}

/*tells the megaman whether he can jump*/
//todo make more general
void MyContactListener::setJump(b2Fixture* fixture,bool state){
	void* bodyUserData=fixture->GetBody()->GetUserData();
	Megaman* megaman= (Megaman*)bodyUserData;
	megaman->canJump=state;
}

/*checks to see if any fixture was foot sensor, and enables/disables jump*/
void MyContactListener::setAllJumps(b2Contact* contact,bool state) {
	//check if fixture A was the foot sensor
	void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	//if not int its pointer so no big risk in cast
	if (((int) fixtureUserData) == JUMPSENSOR) {
		setJump(contact->GetFixtureA(), state);
	}
	//check if fixture B was the foot sensor
	fixtureUserData = contact->GetFixtureB()->GetUserData();
	if (((int) fixtureUserData) == JUMPSENSOR) {
		setJump(contact->GetFixtureB(), state);
	}
}

void MyContactListener::BeginContact(b2Contact* contact) {
	//check if fixture A was the foot sensor
	setAllJumps(contact,true);
}

void MyContactListener::EndContact(b2Contact* contact) {
	setAllJumps(contact,false);
}
