/*
 * KeyMap.h
 *
 *  Created on: Jun 4, 2016
 *      Author: freddy
 */

#ifndef CLIENT_KEYMAP_H_
#define CLIENT_KEYMAP_H_

#include <map>

#include "../common/Thread.h"

typedef unsigned int uint;

class KeyMap {
private:
	Mutex m;
	std::map<uint, bool> keyboard;
public:
	KeyMap();
	virtual ~KeyMap();

	void setState(uint keyId, bool pressed);
	uint getKeyboardState();
};

#endif /* CLIENT_KEYMAP_H_ */
