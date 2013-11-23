/*
 * NamedOneWireSensor.h
 *
 *  Created on: 20. 11. 2013.
 *      Author: Dean
 */

#ifndef NAMEDONEWIRESENSOR_H_
#define NAMEDONEWIRESENSOR_H_

#include "OneWire.h"
#include "OneWireFactory.h"
#include "NamedSensor.h"

class NamedOneWireSensor: public NamedSensor {
private:
	uint8_t pin;
	byte type_s;
	const byte* address;
protected:
	void readSensors();
public:
	NamedOneWireSensor(uint8_t pin, const byte* address, const char * name);
	virtual ~NamedOneWireSensor();
};

#endif /* NAMEDONEWIRESENSOR_H_ */
