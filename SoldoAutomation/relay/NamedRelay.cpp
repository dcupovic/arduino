/*
 * NamedRelay.cpp
 *
 *  Created on: 26. 11. 2013.
 *      Author: Dean
 */

#include "NamedRelay.h"

NamedRelay::NamedRelay(byte pin, int address, const char * name): PersistentRelay(address, pin),
 sname(name), NamedSensor(1, &sname, 1) {
	// TODO Auto-generated constructor stub

}

void NamedRelay::doReadSensors() {
	sensorValues[0].integerReading = isOn()? 1 : 0;
}

NamedRelay::~NamedRelay() {
	// TODO Auto-generated destructor stub
}

SensorState NamedRelay::getState(byte valueId) {
	return OK;
}

SensorValueType NamedRelay::getValueType(byte valueId) {
	return INTEGER_VALUE;
}
