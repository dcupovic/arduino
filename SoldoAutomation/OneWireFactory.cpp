/*
 * OneWireFactory.cpp
 *
 *  Created on: 20. 11. 2013.
 *      Author: Dean
 */

#include "OneWireFactory.h"

int OneWireFactory::numOneWires = 0;
OneWire* OneWireFactory::oneWires[MAX_PINS];
uint8_t OneWireFactory::pins[MAX_PINS];

OneWire* OneWireFactory::getForPin(uint8_t pin) {
	uint8_t foundPin = MAX_PINS;
	for(int i = 0; i < numOneWires; ++i) {
		if(pins[i] == pin)
			foundPin = i;
	}
	if(foundPin == MAX_PINS) { //not found
		if(numOneWires < MAX_PINS) {
			oneWires[numOneWires] = new OneWire(pin);
			pins[numOneWires] = pin;
			return oneWires[numOneWires++];
		}
		else
			return NULL;
	} else { //found
		return oneWires[foundPin];
	}
}
