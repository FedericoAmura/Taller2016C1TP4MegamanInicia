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
#include <iomanip>		//setprecision
#include <iostream>		//fixed

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
void Weapon::shoot(const b2Vec2& pos, int direction){
	if(cooldown.getCurrent()==0){
		Json::Value weaponInfo = getJson();
		int bulletId=weaponInfo["bulletId"].asInt();
		Json::Value speed=weaponInfo["speed"];
		b2Vec2 speedVec(speed["x"].asFloat(),speed["y"].asFloat());
		if(direction==0){
			speedVec.x=-1*speedVec.x;
		}
		BulletInfo* info= new BulletInfo(bulletId,pos,speedVec,groupBits);
		level->newObject(info);
		cooldown.maxOut();
		LOG(INFO)<<std::fixed<<std::setprecision(2)
				<<"firing bullet: "<<bulletId<<" at: "
				<<pos.x<<"-"<<pos.y
				<<"	speed: "<<speedVec.x<<" "<<speedVec.y;
	}
}

/*sets the collision group for the bullets*/
void Weapon::setOwner(int16 group) {
	groupBits=group;
}

/*reduces cooldown by time*/
void Weapon::tick(float time) {
	cooldown.dec(time);
}
