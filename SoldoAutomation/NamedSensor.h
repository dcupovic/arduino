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
	byte numSensors;
	const char* const* sensorNames;
	unsigned long int frequency, lastReadTime;
	bool hasCooledOff();
protected:
	SensorState* sensorStates;
	SensorReading* sensorValues;
	virtual void doReadSensors() = 0;
public:
	NamedSensor(const byte numSensors, const char* const* names, unsigned long int frequency);
	virtual ~NamedSensor();
	float valueF(byte valueId = 0);
	int valueI(byte valueId = 0);
	virtual SensorState getState(byte valueId = 0);
	virtual SensorValueType getValueType(byte valueId = 0);
	byte getNumSensors();
	const char * getName(byte valueId = 0);
	void readSensors();
};

void SensorPrint(Print &print, NamedSensor &sensor);
void SensorPrint(Print &print, NamedSensor &sensor, byte valueId);
void SensorPrintLn(Print &print, NamedSensor &sensor);
void SensorPrintLn(Print &print, NamedSensor &sensor, byte valueId);

#endif /* NAMEDSENSOR_H_ */
