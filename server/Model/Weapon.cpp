/*
 * Weapom.cpp
 *
 *  Created on: May 30, 2016
 *      Author: nicolas
 */

#include "Weapon.h"
#include "../entities.h"
#include "MyLevel.h"
#include "ObjectInfo.h"
#include <fstream>
#include <sstream>
#include <glog/logging.h>

#define COFIG_FILE "../server/Model/config.json"

Weapon::Weapon(int id,MyLevel* lvl,int group):
level(lvl),
weaponId(id),
groupBits(group),
cooldown(getJson()["cooldown"].asFloat()){}

Weapon::~Weapon() {}

/*gets the jason value for the particular weapon*/
Json::Value Weapon::getJson() {
	Json::Value config_json;
	std::ifstream configFile(COFIG_FILE);
	configFile >> config_json;
	std::stringstream ss;
	ss << weaponId;
	Json::Value weaponInfo = config_json[ss.str()];
	return weaponInfo;
}

/*creates bullets with the json details*/
void Weapon::shoot(const b2Vec2& pos){
	if(cooldown.getCurrent()==0){
		Json::Value weaponInfo = getJson();
		int bulletId=weaponInfo["bulletId"].asInt();
		Json::Value speed=weaponInfo["speed"];
		b2Vec2 speedVec(speed["x"].asFloat(),speed["y"].asFloat());
		BulletInfo* info= new BulletInfo(bulletId,pos,speedVec,groupBits);
		level->newObject(info);
		cooldown.maxOut();
//		LOG(INFO)<<"firing bullet: "<<bulletId<<" at: "
//				<<(int)pos.x<<"-"<<(int)pos.y
//				<<"	speed: "<<(int)speedVec.x<<"-"<<(int)speedVec.y;
	}
}

/*sets the collision group for the bullets*/
void Weapon::setOwner(int group) {
	groupBits=group;
}

/*reduces cooldown by time*/
void Weapon::tick(float time) {
	cooldown.dec(time);
}
