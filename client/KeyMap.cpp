/*
 * KeyMap.cpp
 *
 *  Created on: Jun 4, 2016
 *      Author: freddy
 */

#include "KeyMap.h"

#include "../common/MegamanBeginsConstants.h"

KeyMap::KeyMap() {
	keyboard[KEY_1_ID] = false;
	keyboard[KEY_2_ID] = false;
	keyboard[KEY_3_ID] = false;
	keyboard[KEY_4_ID] = false;
	keyboard[KEY_5_ID] = false;
	keyboard[KEY_DOWN_ID] = false;
	keyboard[KEY_ESC_ID] = false;
	keyboard[KEY_LEFT_ID] = false;
	keyboard[KEY_RIGHT_ID] = false;
	keyboard[KEY_SPACE_ID] = false;
	keyboard[KEY_UP_ID] = false;
}

KeyMap::~KeyMap() {
}

void KeyMap::setState(uint keyId, bool pressed) {
	Lock l(m);
	keyboard[keyId] = pressed;
}

uint KeyMap::getKeyboardState() {
	uint state = 0;
	Lock l(m);
	for (std::map<uint,bool>::iterator it=keyboard.begin(); it!=keyboard.end(); ++it){
		if (it->second) state+=it->first;
	}
	return state;
}
