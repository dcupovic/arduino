// Do not remove the include below
#include "SoldoAutomation.h"


//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(57600);
	initSensors();
	initLCD();
	initIR();
	initTime();
	//initEthernet();
}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
	readSensors();
	for(int i = 0; i < SOLDO_SENSORS_COUNT; ++i)
		SensorPrintLn(Serial, *(soldoSensors[i]));
	Serial.println("============");
	loopIR();
	loopLCD();
//	loopEthernet();
	//digitalClockDisplay();
	delay(100);
}
