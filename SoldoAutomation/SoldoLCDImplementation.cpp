/*
 * SoldoLCDImplementation.cpp
 *
 *  Created on: 25. 11. 2013.
 *      Author: Dean
 */

#include "SoldoLCDImplementation.h"

LiquidCrystal_I2C lcdDisplay(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
SoldoLCD lcd(lcdDisplay, soldoSensors);

void initLCD() {
	lcdDisplay.begin(16, 2);
}

void loopLCD() {
	lcd.display();
}

void setPage(byte page) {
	lcd.setPage(page);
}
