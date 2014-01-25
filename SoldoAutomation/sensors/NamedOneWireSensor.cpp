/*
 * NamedOneWireSensor.cpp
 *
 *  Created on: 20. 11. 2013.
 *      Author: Dean
 */

#include "NamedOneWireSensor.h"

NamedOneWireSensor::NamedOneWireSensor(uint8_t pin, const byte* address,
		const char* name) :
		NamedSensor(1, &sname, 5000u), pin(pin), address(address), sname(name) {
	switch (address[0]) {
	case 0x10:
		type_s = 1;
		break;
	case 0x28:
		type_s = 0;
		break;
	case 0x22:
		type_s = 0;
		break;
	}
}

void NamedOneWireSensor::doReadSensors() {
	OneWire* oneWire = OneWireFactory::getForPin(pin);
	static byte data[12];
	static byte present;
	oneWire->reset();
	oneWire->select(address);
	oneWire->write(0x44, 1);        // start conversion, with parasite power on at the end

	delay(50);
	// not sure what to put here, since they have external power source
	// all the examples are with parasite power which requires some time
	// for sensor to "charge". With external power source this should not be
	// necessary and large pause makes other things (especially LCD)  less
	// responsive.


	present = oneWire->reset();
	oneWire->select(address);
	oneWire->write(0xBE);         // Read Scratchpad
	for (int i = 0; i < 9; i++) {           // we need 9 bytes
		data[i] = oneWire->read();
	}
	if(oneWire->crc8(data, 8) != data[8]) {
		sensorStates[0] = ERROR_READING;
		return;
	} else
		sensorStates[0] = OK;
	int16_t raw = (data[1] << 8) | data[0];
	if (type_s) {
		raw = raw << 3; // 9 bit resolution default
		if (data[7] == 0x10) {
			// "count remain" gives full 12 bit resolution
			raw = (raw & 0xFFF0) + 12 - data[6];
		}
	} else {
		byte cfg = (data[4] & 0x60);
		// at lower res, the low bits are undefined, so let's zero them
		if (cfg == 0x00)
			raw = raw & ~7;  // 9 bit resolution, 93.75 ms
		else if (cfg == 0x20)
			raw = raw & ~3; // 10 bit res, 187.5 ms
		else if (cfg == 0x40)
			raw = raw & ~1; // 11 bit res, 375 ms
		//// default is 12 bit resolution, 750 ms conversion time
	}
	sensorValues[0].floatReading = (float) raw / 16.0;
}

NamedOneWireSensor::~NamedOneWireSensor() {
	// TODO Auto-generated destructor stub
}

