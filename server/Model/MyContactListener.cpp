/*
 * MyContactListener.cpp
 *
 *  Created on: May 29, 2016
 *      Author: nicolas
 */

#include <cstdint>
#include "MyContactListener.h"
#include "LevelObject.h"
#include <glog/logging.h>
#include "Character.h"
#include "Megaman.h"
#include "Obstacle.h"

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
	Character* character= (Character*)bodyUserData;
	if(state){
		character->surfacesTouching++;
		if(character->surfacesTouching>0)
			character->canJump=true;
	}else{
		if(character->surfacesTouching>0)
			character->surfacesTouching--;
		if(character->surfacesTouching==0)
					character->canJump=false;
	}

}

/*checks to see if any fixture was foot sensor, and enables/disables jump*/
void MyContactListener::setAllJumps(b2Contact* contact,bool state) {
	//check if fixture A was the foot sensor
	intptr_t fixtureUserData = (intptr_t)contact->GetFixtureA()->GetUserData();

	//if not int its pointer so no big risk in cast
	if (fixtureUserData) {
		setJump(contact->GetFixtureA(), state);
	}
	//check if fixture B was the foot sensor
	fixtureUserData = (intptr_t)contact->GetFixtureB()->GetUserData();
	if (fixtureUserData) {
		setJump(contact->GetFixtureB(), state);
	}
}

void MyContactListener::BeginContact(b2Contact* contact) {
	setAllJumps(contact,true);

	void* userData1=contact->GetFixtureA()->GetBody()->GetUserData();
	void* userData2=contact->GetFixtureB()->GetBody()->GetUserData();
	LevelObject* obj1=(LevelObject*)userData1;
	LevelObject* obj2=(LevelObject*)userData2;
	obj1->collideWith(obj2);
	obj2->collideWith(obj1);
}

void MyContactListener::EndContact(b2Contact* contact) {
	setAllJumps(contact,false);
	void* userData1=contact->GetFixtureA()->GetBody()->GetUserData();
	void* userData2=contact->GetFixtureB()->GetBody()->GetUserData();
	LevelObject* obj1=(LevelObject*)userData1;
	LevelObject* obj2=(LevelObject*)userData2;
	obj1->stopCollidingWith(obj2);
	obj2->stopCollidingWith(obj1);
}
