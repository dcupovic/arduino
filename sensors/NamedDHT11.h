/*
 * NamedDHT11.h
 *
 *  Created on: 14. 11. 2013.
 *      Author: Dean
 */

#ifndef NAMEDDHT11_H_
#define NAMEDDHT11_H_

#include "NamedSensor.h"
#include "dht11.h"

class NamedDHT11: public NamedSensor {
private:
	static dht11 DHT11;
	int pin;
protected:
	int readSensorI(int valueId, SensorState &state);
	float readSensorF(int valueid, SensorState &state);
public:
	NamedDHT11(int pin, char ** names);
	virtual ~NamedDHT11();
};

#endif /* NAMEDDHT11_H_ */
