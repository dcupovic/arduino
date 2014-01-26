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
unsigned long lastSendTime;
EthernetClient client;
EthernetServer server(80);
String readString;

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

void sendData() {
	request[0] = '?';
	int sensorsRead = buildRequestString(soldoSensors, SOLDO_SENSORS_COUNT,
			request + 1);
	if (sensorsRead > 0) {

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
		int cc = 20000;
		while (client.connected() && !client.available()) {
			delay(1); //waits for data
			if(cc--) break;
		}
		while (client.connected() || client.available()) { //connected or data available
			char c = client.read();
			//Serial.print(c);
		}
		Serial.println();
		Serial.println("disconnecting.");
		Serial.println("==================");
		Serial.println();
		client.stop();
	}
}

void loopServer() {
	EthernetClient client = server.available();
	if (client) {
		while (client.connected()) {
			if (client.available()) {
				char c = client.read();

				//read char by char HTTP request
				if (readString.length() < 100) {

					//store characters to string
					readString += c;
					//Serial.print(c);
				}

				//if HTTP request has ended
				if (c == '\n') {

					///////////////
					Serial.print(readString); //print to serial monitor for debuging

					//now output HTML data header
					client.println(F("HTTP/1.1 200 OK")); //send new page on browser request
					client.println(F("Content-Type: text/html"));
					client.println();

					client.println(F("Ok"));

					delay(1);
					//stopping client
					client.stop();

					if (readString.indexOf("R1=1") > 0){
						soldoRelays[0]->On();
//						Serial.println(">>>>>>>>>>>>");
//						Serial.println("R1=1");
					}
					if (readString.indexOf("R2=1") > 0){
						soldoRelays[1]->On();
//						Serial.println(">>>>>>>>>>>>");
//						Serial.println("R2=1");
					}
					if (readString.indexOf("R1=0") > 0){
						soldoRelays[0]->Off();
//						Serial.println(">>>>>>>>>>>>");
//						Serial.println("R1=0");
					}
					if (readString.indexOf("R2=0") > 0){
						soldoRelays[1]->Off();
//						Serial.println(">>>>>>>>>>>>");
//						Serial.println("R2=0");
					}
					readString="";

				}
			}
		}
	}
}

void loopEthernet() {

	//Client
	if (lastSendTime - millis() > ETHERNET_REPORTING_FREQUENCY_MS) {
		lastSendTime += ETHERNET_REPORTING_FREQUENCY_MS;
		sendData();
	}
	//Server
	loopServer();
}

