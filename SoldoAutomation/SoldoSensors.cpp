/*
 * SoldoSensors.cpp
 *
 *  Created on: 23. 11. 2013.
 *      Author: Dean
 */
#include "SoldoSensors.h"


NamedSensor* soldoSensors[SOLDO_SENSORS_COUNT];
//DHTs
const char* PROGMEM dhtNameT1 = "TZ1";
const char* PROGMEM dhtNameV1 = "VZ1%";
const char* PROGMEM dhtNameT2 = "TZ2";
const char* PROGMEM dhtNameV2 = "VZ2%";

const char * const dhtNames1[] = {dhtNameT1, dhtNameV1};
const char * const dhtNames2[] = {dhtNameT2, dhtNameV2};

//OneWire
const char* PROGMEM TName1 = "T1";
const char* PROGMEM TName2 = "T2";
const char* PROGMEM TName3 = "T3";
const char * const TNames1[] = {TName1};
const byte  T1Address[] = {0x28, 0x3A, 0x70, 0xAC, 0x04, 0x00 ,0x00, 0x74};
const byte  T2Address[] = {0x28, 0x16, 0xBF, 0xAB, 0x04, 0x00 ,0x00, 0x74};
const byte  T3Address[] = {0x28, 0x4B, 0x28, 0xAC, 0x04, 0x00 ,0x00, 0x70};

void initSensors() {
	soldoSensors[0] = new NamedDHT11(PORT2_WIRE5_PIN, dhtNames1);
	soldoSensors[1] = new NamedDHT11(PORT2_WIRE6_PIN, dhtNames2);
	soldoSensors[2] = new NamedOneWireSensor(PORT2_WIRE4_PIN, T1Address,
			TName1);
	soldoSensors[3] = new NamedOneWireSensor(PORT2_WIRE4_PIN, T2Address,
			TName2);
	soldoSensors[4] = new NamedOneWireSensor(PORT2_WIRE4_PIN, T3Address,
			TName3);
}

void readSensors() {
	for(int i = 0; i < SOLDO_SENSORS_COUNT; ++i)
		soldoSensors[i]->readSensors();
}
