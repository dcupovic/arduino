/*
 * NamedSensor.cpp
 *
 *  Created on: 12. 11. 2013.
 *      Author: Dean
 */

#include "NamedSensor.h"

NamedSensor::NamedSensor(const unsigned char numSensors, const char* const* names,
		unsigned long int frequency) {
	this->numSensors = numSensors;
	this->sensorNames = names;
	this->sensorValues = new SensorReading[numSensors];
	this->sensorStates = new SensorState[numSensors];
	this->frequency = frequency;
	this->lastReadTime = millis() - 1000;
	for (unsigned char i = 0; i < numSensors; ++i) {
		this->sensorStates[i] = NOT_READ;
	}
}

NamedSensor::~NamedSensor() {
	// TODO Auto-generated destructor stub
}

bool NamedSensor::hasCooledOff() {
	unsigned long int now = millis();
	if((now - this->lastReadTime) >= this->frequency) {
		lastReadTime = now;
		return true;
	}
	return false;
}

float NamedSensor::valueF(unsigned char valueId) {
	if(hasCooledOff()) {
		readSensors();
	}
	return sensorValues[valueId].floatReading;
}

int NamedSensor::valueI(unsigned char valueId) {
	if(hasCooledOff()) {
		readSensors();
	}
	return sensorValues[valueId].integerReading;
}

SensorState NamedSensor::getState(unsigned char valueId) {
	return sensorStates[valueId];
}

SensorValueType NamedSensor::getValueType(unsigned char valueId) {
	return FLOAT_VALUE;
}

void SensorPrint(Print& print, NamedSensor& sensor) {
	for (unsigned char i = 0; i < sensor.getNumSensors(); ++i) {
		SensorPrint(print, sensor, i);
		if(i>0)
			print.print(", ");
	}
}

void SensorPrint(Print& print, NamedSensor& sensor, unsigned char valueId) {
	print.print(sensor.getName(valueId));
	print.print(": ");
	switch (sensor.getState(valueId)) {
	OK: if (sensor.getValueType(valueId) == FLOAT_VALUE)
		print.print(sensor.valueF(valueId), 1);
	if (sensor.getValueType(valueId) == INTEGER_VALUE)
		print.print(sensor.valueI());
	break;
	NOT_READ: print.print("?");
	break;
	ERROR_READING: print.print("!");
	break;
	}
}

void SensorPrintLn(Print& print, NamedSensor& sensor) {
	for(unsigned char i = 0; i < sensor.getNumSensors(); ++i)
		SensorPrintLn(print, sensor, i);
}

void SensorPrintLn(Print& print, NamedSensor& sensor, unsigned char valueId) {
	SensorPrint(print, sensor, valueId);
	print.println();
}

unsigned char NamedSensor::getNumSensors() {
	return numSensors;
}

const char* NamedSensor::getName(unsigned char valueId) {
	return sensorNames[valueId];
}
