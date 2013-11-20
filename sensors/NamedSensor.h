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
enum SensorValueType {FLOAT_VALUE, INTEGER_VALUE};

class NamedSensor {
private:
	unsigned char numSensors;
	const char* const* sensorNames;
	unsigned long int frequency, lastReadTime;
	bool hasCooledOff();
protected:
	SensorState* sensorStates;
	SensorReading* sensorValues;
	virtual void readSensors() = 0;
public:
	NamedSensor(const unsigned char numSensors, const char* const* names, unsigned long int frequency);
	virtual ~NamedSensor();
	float valueF(int valueId = 0);
	int valueI(int valueId = 0);
	SensorState getState(int valueId);
	virtual SensorValueType getValueType(int valueId);
};

#endif /* NAMEDSENSOR_H_ */
