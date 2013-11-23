/*
 * NamedSensor.h
 *
 *  Created on: 12. 11. 2013.
 *      Author: Dean
 */

#ifndef NAMEDSENSOR_H_
#define NAMEDSENSOR_H_

#include "Arduino.h"
#include "Print.h"

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
	float valueF(unsigned char valueId = 0);
	int valueI(unsigned char valueId = 0);
	SensorState getState(unsigned char valueId = 0);
	virtual SensorValueType getValueType(unsigned char valueId = 0);
	unsigned char getNumSensors();
	const char * getName(unsigned char valueId = 0);
};

void SensorPrint(Print &print, NamedSensor &sensor);
void SensorPrint(Print &print, NamedSensor &sensor, unsigned char valueId);
void SensorPrintLn(Print &print, NamedSensor &sensor);
void SensorPrintLn(Print &print, NamedSensor &sensor, unsigned char valueId);

#endif /* NAMEDSENSOR_H_ */
