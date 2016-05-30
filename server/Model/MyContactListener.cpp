/*
 * MyContactListener.cpp
 *
 *  Created on: May 29, 2016
 *      Author: nicolas
 */

#include "MyContactListener.h"
#include "Megaman.h"
#include "LevelObject.h"
#include <glog/logging.h>

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
	setAllJumps(contact,true);

	uint16 catBits1=contact->GetFixtureA()->GetFilterData().categoryBits;
	//LOG(INFO)<<"cat bits 1: "<<catBits1;
	uint16 catBits2=contact->GetFixtureB()->GetFilterData().categoryBits;
	//LOG(INFO)<<"cat bits 2: "<<catBits2;
	uint16 boundary=BOUNDARY;
	//si ninguno es borde les pido que colisionen como objetos
	if(((catBits1 | catBits2) & boundary)==0){
		LOG(INFO)<<"COLLISION";
		void* userData1=contact->GetFixtureA()->GetBody()->GetUserData();
		void* userData2=contact->GetFixtureB()->GetBody()->GetUserData();
		LevelObject* obj1=(LevelObject*)userData1;
		LevelObject* obj2=(LevelObject*)userData2;
		obj1->collideWith(obj2);
		obj2->collideWith(obj1);
	}
}

void MyContactListener::EndContact(b2Contact* contact) {
	setAllJumps(contact,false);
}
