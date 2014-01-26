/*
 * SoldoEthernet.cpp
 *
 *  Created on: 27. 11. 2013.
 *      Author: Dean
 */
#include "SoldoEthernet.h"

static byte mymac[] = { 0x74, 0x69, 0x69, 0x2d, 0xa0, 0x31 };

#define _SOLDO

#ifdef SOLDO
static IPAddress myip(192,168,1,200);
static IPAddress gwip(192,168,1,1);
#else
static IPAddress myip(192, 168, 14, 200);
static IPAddress gwip(192, 168, 14, 1);
#endif
static IPAddress mydns(8, 8, 8, 8);

#ifdef SOLDO
char website[] PROGMEM = "192.168.1.100";
static IPAddress serverIp(192,168,1,100);
#else
char website[] PROGMEM = "192.168.14.157";
static IPAddress serverIp(192, 168, 14, 157);
#endif

static char request[50];
static bool initialized;
unsigned long lastSendTime;
EthernetClient client;
boolean lastConnected = false;

void initEthernet() {
	lastSendTime = millis();
	delay(1000);
	Ethernet.begin(mymac, myip, mydns);
}

int buildRequestString(NamedSensor* sensors[], int numSensors,
		char* requestString) {
	int count = 0;
	bool first = true;
	char *r = requestString;
	static char shortName[4];
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
					long f = (long) (sensors[i]->valueF(j) * 100.0);
					r = r
							+ sprintf(r, "%d.%02d", (int) (f / 100),
									(int) (f % 100));
					break;
				}
				++count;
			}
		}
	}
	return count;
}

void loopEthernet() {

	while (client.available() && client.connected()) {
		char c = client.read();
		Serial.print(c);
	}

	if (!client.connected() && lastConnected) {
		Serial.println();
		Serial.println("disconnecting.");
		client.stop();
	}

	if (lastSendTime - millis() > ETHERNET_REPORTING_FREQUENCY_MS) {
		lastSendTime += ETHERNET_REPORTING_FREQUENCY_MS;
		request[0] = '?';
		int sensorsRead = buildRequestString(soldoSensors, SOLDO_SENSORS_COUNT,
				request + 1);
		if (sensorsRead > 0) {
			Serial.println(request);
			if (client.connect(serverIp, 80)) {
				Serial.println("connecting...");
				// send the HTTP PUT request:
				client.print("GET /index.py");
				client.print(request);
				client.println(" HTTP/1.0");
				client.println();

			} else {
				// if you couldn't make a connection:
				Serial.println("connection failed");
				Serial.println("disconnecting.");
				client.stop();
			}
		}
	}

	lastConnected = client.connected();
}

