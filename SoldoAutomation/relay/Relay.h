/*
 * Relay.h
 *
 *  Created on: 26. 11. 2013.
 *      Author: Dean
 */

#ifndef RELAY_H_
#define RELAY_H_

#include "Arduino.h"

class Relay {
private:
	bool state;
	byte pin;
public:
	Relay(byte pin, bool initialState = false);
	virtual void On();
	virtual void Off();
	bool isOn();
	virtual ~Relay();
};

#endif /* RELAY_H_ */
