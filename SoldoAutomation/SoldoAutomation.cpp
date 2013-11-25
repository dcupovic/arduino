// Do not remove the include below
#include "SoldoAutomation.h"

//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
	initSensors();
	initLCD();
	Serial.begin(57600);
}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
	readSensors();
	for(int i = 0; i < SOLDO_SENSORS_COUNT; ++i)
		SensorPrintLn(Serial, *(soldoSensors[i]));
	Serial.println("============");
	loopLCD();
	delay(2000);
}
