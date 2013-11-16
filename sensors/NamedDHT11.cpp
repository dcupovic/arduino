/*
 * NamedDHT11.cpp
 *
 *  Created on: 14. 11. 2013.
 *      Author: Dean
 */

#include "NamedDHT11.h"

char** NamedDHT11::doubleName(char* name) {
	char ** names = new char* [2];
	names[0] = new char[strlen(name) + 2];
	names[1] = new char[strlen(name) + 2];
	names[0][0] = 'T';
	names[1][0] = 'V';
	strcpy(names[0] + 1, name);
	strcpy(names[1] + 1, name);
	return names;
}


NamedDHT11::NamedDHT11(int pin, char * name) : NamedSensor(2u, &name, 5000u), pin(pin) {

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

