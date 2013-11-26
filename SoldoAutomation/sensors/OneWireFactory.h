/*
 * OneWireFactory.h
 *
 *  Created on: 20. 11. 2013.
 *      Author: Dean
 */

#ifndef ONEWIREFACTORY_H_
#define ONEWIREFACTORY_H_

#include "OneWire.h"
#define MAX_PINS 4

class OneWireFactory {
private:
	static int numOneWires;
	static OneWire* oneWires[MAX_PINS];
	static uint8_t pins[MAX_PINS];
public:
	static OneWire* getForPin(uint8_t pin);
};

#endif /* ONEWIREFACTORY_H_ */
