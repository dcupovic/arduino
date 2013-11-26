/*
 * SoldoLCD.cpp
 *
 *  Created on: 25. 11. 2013.
 *      Author: Dean
 */

#include "SoldoLCD.h"

SoldoLCD::SoldoLCD(LCD& lcd, NamedSensor** sensors) :
		PagedLCD(lcd, 3), sensors(sensors) {
	// TODO Auto-generated constructor stub
}

void SoldoLCD::displayPage(byte page) {
	switch (page) {
	case 0:
		goto1of4();
		SensorPrint(lcd, *(sensors[0]), 0);
		printSpaces();
		goto2of4();
		SensorPrint(lcd, *(sensors[0]), 1);
		printSpaces();
		goto3of4();
		SensorPrint(lcd, *(sensors[1]), 0);
		printSpaces();
		goto4of4();
		SensorPrint(lcd, *(sensors[1]), 1);
		printSpaces();
		break;
	case 1:
		goto1of4();
		SensorPrint(lcd, *(sensors[2]), 0);
		printSpaces();
		goto2of4();
		SensorPrint(lcd, *(sensors[3]), 0);
		printSpaces();
		goto3of4();
		SensorPrint(lcd, *(sensors[4]), 0);
		printSpaces();
		goto4of4();
		printSpaces();
		break;
	case 2:
		goto1of4();
		digitalDateDisplay(lcd);
		printSpaces();
		goto3of4();
		digitalTimeDisplay(lcd);
		printSpaces();
		break;
	}
}

void SoldoLCD::goto1of2() {
	goto1of4();
}

void SoldoLCD::goto2of2() {
	goto3of4();
}

void SoldoLCD::goto1of4() {
	lcd.setCursor(0, 0);
}

void SoldoLCD::goto2of4() {
	lcd.setCursor(8, 0);
}

void SoldoLCD::goto3of4() {
	lcd.setCursor(0, 1);
}

void SoldoLCD::goto4of4() {
	lcd.setCursor(8, 1);
}

void SoldoLCD::printSpaces() {
	lcd.print("        ");
}

SoldoLCD::~SoldoLCD() {
	// TODO Auto-generated destructor stub
}

