/*
 * NamedSensor.h
 *
 *  Created on: 12. 11. 2013.
 *      Author: Dean
 */

#ifndef NAMEDSENSOR_H_
#define NAMEDSENSOR_H_

#include "Arduino.h"

union SensorReading {
	float floatReading;
	int integerReading;
};

enum SensorState {NOT_READ, ERROR_READING, OK };

class NamedSensor {
private:
	unsigned char numSensors;
	char** sensorNames;
	SensorState* sensorStates;
	SensorReading* values;
	unsigned long int frequency, lastReadTime;
	bool hasCooledOff();
protected:
	virtual int readSensorI(int valueId, SensorState &state) = 0;
	virtual float readSensorF(int valueid, SensorState &state) = 0;
public:
	NamedSensor(const unsigned char numSensors, char** names, unsigned long int frequency);
	virtual ~NamedSensor();
	float valueF(int valueId = 0);
	int valueI(int valueId = 0);
	SensorState getState(int valueId);
};

#endif /* NAMEDSENSOR_H_ */
