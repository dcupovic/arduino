/*
 * NamedDHT11.h
 *
 *  Created on: 14. 11. 2013.
 *      Author: Dean
 */

#ifndef NAMEDDHT11_H_
#define NAMEDDHT11_H_

#define _DEBUG
#include "NamedSensor.h"
#include "dht11.h"

class NamedDHT11: public NamedSensor {
private:
	static dht11 DHT11;
	int pin;
protected:
	void doReadSensors();
public:
	NamedDHT11(int pin, const char * const * names);
	virtual ~NamedDHT11();
	SensorValueType getValueType(byte valueId);
};

#endif /* NAMEDDHT11_H_ */
