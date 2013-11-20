// Do not remove the include below
#include "sensors.h"

const char* PROGMEM dhtNameT1 = "VZ1";
const char*  PROGMEM dhtNameV1 = "VZ1";

const char * const dhtNames[] = {dhtNameT1, dhtNameT1};

NamedDHT11 dht1(1, dhtNames);
NamedOneWireSensor n(2, NULL, "aa");
//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
	Serial.begin(57600);
}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
	int t = dht1.valueI(0);
	int v = dht1.valueI(1);

}
