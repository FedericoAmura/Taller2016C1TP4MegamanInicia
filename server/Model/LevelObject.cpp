/*
 * LevelObject.cpp
 *
 *  Created on: May 24, 2016
 *      Author: nicolas
 */

#include "LevelObject.h"
#include <Box2D/Box2D.h>
#include "../json/json.h"
#include <string>
#include <glog/logging.h>

int LevelObject::uniqueId=0;

/*creates a new object,at pos, with its config from file*/
LevelObject::LevelObject(b2World* w,Json::Value& json,const b2Vec2& pos,int id)
:world(w),objectId(uniqueId++),spriteId(id){
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(pos.x,pos.y);
	body = world->CreateBody(&bodyDef);
	body->SetUserData(this);
	Json::Value shapes=json["shapes"];
	Json::ValueIterator shapesIt=shapes.begin();
	for(; shapesIt!=shapes.end(); shapesIt++){
		createFixture(*shapesIt);
	}
}

enum _shapeTypes{
	BOX=		1,
	CIRCLE=		2,
	TRIANGLE=	3,
	EDGE=		4,
};

/*determines type and sets the shape from the json
 * delete shape after use*/
void LevelObject::createFixture(Json::Value& jsonShape) {
	b2FixtureDef fixtureDef;
	int shapeType=jsonShape["type"].asInt();
	/*note: the addFixture is in each case because of the shape scope*/
	switch(shapeType){
	case BOX:{
		b2PolygonShape box;
		b2Vec2 pos(jsonShape["X"].asFloat(),jsonShape["Y"].asFloat());
		box.SetAsBox(jsonShape["width"].asFloat(),
				jsonShape["height"].asFloat(),
				pos,0);
		fixtureDef.shape =&box;
		this->addFixture(fixtureDef);
		break;
	}
	case CIRCLE:{
		b2CircleShape circle;
		circle.m_p.Set(jsonShape["X"].asFloat(),jsonShape["Y"].asFloat());
		circle.m_radius = jsonShape["radius"].asFloat();
		fixtureDef.shape =&circle;
		this->addFixture(fixtureDef);
		break;
	}
	case TRIANGLE:{
		b2PolygonShape triangle;
		b2Vec2 vertices[3];
		vertices[0].Set(jsonShape["X1"].asFloat(),jsonShape["Y1"].asFloat());
		vertices[1].Set(jsonShape["X2"].asFloat(),jsonShape["Y2"].asFloat());
		vertices[2].Set(jsonShape["X3"].asFloat(),jsonShape["Y3"].asFloat());
		triangle.Set(vertices,3);
		fixtureDef.shape =&triangle;
		this->addFixture(fixtureDef);
		break;
	}
	case EDGE:{
		b2EdgeShape edge;
		b2Vec2 pos1(jsonShape["X1"].asFloat(),jsonShape["Y1"].asFloat());
		b2Vec2 pos2(jsonShape["X2"].asFloat(),jsonShape["Y2"].asFloat());
		edge.Set(pos1,pos2);
		fixtureDef.shape =&edge;
		this->addFixture(fixtureDef);
		break;
	}
	default:{
		b2PolygonShape box;
		box.SetAsBox(0.5,0.5);
		fixtureDef.shape =&box;
		this->addFixture(fixtureDef);
		break;
	}
	}
}

/*adds fixture with normal density, no friction or restitution
 * redefine and call super to make sure fixtures collide with corresponding entities*/
b2Fixture* LevelObject::addFixture(b2FixtureDef& fDef) {
	fDef.density = 1.0;
	fDef.friction=0.2;
	fDef.restitution=0;
	return body->CreateFixture(&fDef);
}

/*destroys itself and removes body from world*/
LevelObject::~LevelObject() {
	world->DestroyBody(body);
}

/*returns the position in world coordinates*/
const b2Vec2& LevelObject::getPos() {
	return body->GetPosition();
}

/*returns the unique object id*/
int LevelObject::getId(){
	return objectId;
}

/*returns the object sprite id*/
int LevelObject::getSpriteId() {
	return spriteId;
}

/*returns whether the object has suffered changes*/
bool LevelObject::changed() {
	return body->IsAwake();
}

/*default does nothing, should be redifined in subclass*/
void LevelObject::collideWith(LevelObject* obj) {
}

/*reset the id generator for all objects*/
void LevelObject::resetIds() {
	LevelObject::uniqueId=0;
}

void LevelObject::copyCorner(b2Vec2& corner) {
	corner.x=body->GetPosition().x;
	corner.y=body->GetPosition().y;
}


