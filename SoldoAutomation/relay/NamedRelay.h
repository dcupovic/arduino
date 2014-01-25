/*
 * NamedRelay.h
 *
 *  Created on: 26. 11. 2013.
 *      Author: Dean
 */

#ifndef NAMEDRELAY_H_
#define NAMEDRELAY_H_

#include "PersistentRelay.h"
#include "../sensors/NamedSensor.h"

class NamedRelay: public PersistentRelay, public NamedSensor {
private:
	const char * sname;
protected:
	void doReadSensors();
public:
	NamedRelay(byte pin, int address, const char * name);
	virtual ~NamedRelay();
	SensorState getState(byte valueId = 0);
	SensorValueType getValueType(byte valueId = 0);
};

#endif /* NAMEDRELAY_H_ */
