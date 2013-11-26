/*
 * Relay.cpp
 *
 *  Created on: 26. 11. 2013.
 *      Author: Dean
 */

#include "Relay.h"

#define RELAY_ON LOW
#define RELAY_OFF HIGH

Relay::Relay(byte pin, bool initialState): pin(pin), state(initialState) {
	pinMode(pin, OUTPUT);
}

void Relay::On() {
	state = true;
	digitalWrite(pin, RELAY_ON);
}

void Relay::Off() {
	state = false;
	digitalWrite(pin, RELAY_OFF);
}

bool Relay::isOn() {
	return state;
}

Relay::~Relay() {
	// TODO Auto-generated destructor stub
}

