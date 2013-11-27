/*
 * SoldoEthernet.cpp
 *
 *  Created on: 27. 11. 2013.
 *      Author: Dean
 */
#include "SoldoEthernet.h"

static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

#define _SOLDO

#ifdef SOLDO
static PROGMEM byte myip[] = { 192,168,1,200 };
static PROGMEM byte gwip[] = { 192,168,1,1 };
#else
static PROGMEM byte myip[] = { 192,168,14,200 };
static PROGMEM byte gwip[] = { 192,168,14,1 };
#endif

#ifdef SOLDO
char website[] PROGMEM = "192.168.1.100";
static PROGMEM byte serverIp[] = { 192,168,1,100 };
#else
char website[] PROGMEM = "192.168.14.157";
static PROGMEM byte serverIp[] = { 192,168,14,157 };
#endif

byte Ethernet::buffer[700];
char request[50];
static bool initialized;
unsigned long lastSendTime;

void initEthernet() {
	initialized = false;
	if (ether.begin(sizeof Ethernet::buffer, mymac, ETHERNET_CS_PIN) == 0) {
		Serial.println("Failed to access Ethernet controller");
		return;
	}
	ether.staticSetup(myip, gwip);
	for(int i = 0; i < 4; i++)
		ether.hisip[i] = serverIp[i];
	initialized = true;
	lastSendTime = millis();
}

int buildRequestString(NamedSensor* sensors[], int numSensors, char* requestString) {
	int count = 0;
	bool first = true;
	char *r = requestString;
	char shortName[4];
	for (int i = 0; i < numSensors; ++i) {
		for (int j = 0; j < sensors[i]->getNumSensors(); ++j) {
			if (sensors[i]->getState(j) == OK) {
				strncpy(shortName, sensors[i]->getName(j), 3);
				Serial.println(shortName);
				if (!first)
					r = r + sprintf(r, "&");
				first = false;
				r = r + sprintf(r, "%s=", shortName);
				switch (sensors[i]->getValueType(j)) {
				case INTEGER_VALUE:
					r = r + sprintf(r, "%d", sensors[i]->valueI(j));
					break;
				case FLOAT_VALUE:
					r = r + sprintf(r, "%0.2f", sensors[i]->valueF(j));
					break;
				}
				++count;
			}
		}
	}
	return count;
}

static void my_callback (byte status, word off, word len) {
  Serial.println(">>>");
  Ethernet::buffer[off+300] = 0;
  Serial.print((const char*) Ethernet::buffer + off);
  Serial.println("...");
}

void loopEthernet() {
	ether.packetLoop(ether.packetReceive());
	if(lastSendTime - millis() > ETHERNET_REPORTING_FREQUENCY_MS) {
		lastSendTime += ETHERNET_REPORTING_FREQUENCY_MS;
		int sensorsRead = buildRequestString(soldoSensors, SOLDO_SENSORS_COUNT, request);
		if(sensorsRead > 0) {
			Serial.println(request);
		    ether.browseUrl(PSTR("/index.py"), request, website, my_callback);
		}
	}
}


