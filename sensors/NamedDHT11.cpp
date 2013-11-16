/*
 * NamedDHT11.cpp
 *
 *  Created on: 14. 11. 2013.
 *      Author: Dean
 */

#include "NamedDHT11.h"

NamedDHT11::NamedDHT11(int pin, char ** names) : NamedSensor(2u, names, 5000u), pin(pin) {

}

NamedDHT11::~NamedDHT11() {
	// TODO Auto-generated destructor stub
}

int NamedDHT11::readSensorI(int valueId, SensorState &state) {
	if(DHT11.read(pin) == DHTLIB_OK) {
		state = OK;
		if(valueId == 0)
			return DHT11.temperature;
		else
			return DHT11.humidity;
	}
	else {
		state = ERROR_READING;
	}
	return 0;
}

float NamedDHT11::readSensorF(int valueid, SensorState &state) {
	return 0.0;
}

