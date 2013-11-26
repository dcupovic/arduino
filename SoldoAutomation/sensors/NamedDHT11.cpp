/*
 * NamedDHT11.cpp
 *
 *  Created on: 14. 11. 2013.
 *      Author: Dean
 */

#include "NamedDHT11.h"

dht11 NamedDHT11::DHT11;

NamedDHT11::NamedDHT11(int pin, const char * const * names) : NamedSensor(2u, names, 5000u), pin(pin) {

}

NamedDHT11::~NamedDHT11() {
	// TODO Auto-generated destructor stub
}

void NamedDHT11::doReadSensors() {
	if(DHT11.read(pin) == DHTLIB_OK) {
#ifdef DEBUG
		Serial.print("OK");
#endif
		sensorStates[0] = OK;
		sensorStates[1] = OK;
		sensorValues[0].integerReading = DHT11.temperature;
		sensorValues[1].integerReading = DHT11.humidity;
	}
	else {
		sensorStates[0] = ERROR_READING;
		sensorStates[1] = ERROR_READING;
	}
}

SensorValueType NamedDHT11::getValueType(byte valueId) {
	return INTEGER_VALUE;
}
