/*
 * NamedSensor.cpp
 *
 *  Created on: 12. 11. 2013.
 *      Author: Dean
 */

#include "NamedSensor.h"

NamedSensor::NamedSensor(const byte numSensors, const char* const* names,
		unsigned long int frequency) {
	this->numSensors = numSensors;
	this->sensorNames = names;
	this->sensorValues = new SensorReading[numSensors];
	this->sensorStates = new SensorState[numSensors];
	this->frequency = frequency;
	this->lastReadTime = millis() - 1000;
	for (byte i = 0; i < numSensors; ++i) {
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

float NamedSensor::valueF(byte valueId) {
	return sensorValues[valueId].floatReading;
}

int NamedSensor::valueI(byte valueId) {
	return sensorValues[valueId].integerReading;
}

SensorState NamedSensor::getState(byte valueId) {
	return sensorStates[valueId];
}

SensorValueType NamedSensor::getValueType(byte valueId) {
	return FLOAT_VALUE;
}

void SensorPrint(Print& print, NamedSensor& sensor) {
	for (byte i = 0; i < sensor.getNumSensors(); ++i) {
		if(i>0)
			print.print(", ");
		SensorPrint(print, sensor, i);
	}
}

void SensorPrint(Print& print, NamedSensor& sensor, byte valueId) {
	print.print(sensor.getName(valueId));
	print.print(":");
	switch (sensor.getState(valueId)) {
	case OK:
		//Serial.println(sensor.getValueType(valueId));
		if (sensor.getValueType(valueId) == FLOAT_VALUE)
			print.print(sensor.valueF(valueId), 1);
		if (sensor.getValueType(valueId) == INTEGER_VALUE)
			print.print(sensor.valueI(valueId));
		break;
	case NOT_READ:
		print.print("?");
		break;
	case ERROR_READING:
		print.print("!");
		break;
	}
}

void SensorPrintLn(Print& print, NamedSensor& sensor) {
	for(byte i = 0; i < sensor.getNumSensors(); ++i)
		SensorPrintLn(print, sensor, i);
}

void SensorPrintLn(Print& print, NamedSensor& sensor, byte valueId) {
	SensorPrint(print, sensor, valueId);
	print.println();
}

byte NamedSensor::getNumSensors() {
	return numSensors;
}

const char* NamedSensor::getName(byte valueId) {
	return sensorNames[valueId];
}

void NamedSensor::readSensors() {
	if(hasCooledOff()) {
		doReadSensors();
	}
}
