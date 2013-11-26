/*
 * PagedLCD.cpp
 *
 *  Created on: 25. 11. 2013.
 *      Author: Dean
 */

#include "PagedLCD.h"

PagedLCD::PagedLCD(LCD& lcd, byte numPages) :
		lcd(lcd), numPages(numPages), currentPage(0) {
	// TODO Auto-generated constructor stub
	time = millis();
}

PagedLCD::~PagedLCD() {
	// TODO Auto-generated destructor stub
}

void PagedLCD::display() {
	unsigned long now = millis();
	if(now - time >= 10000) {
		time = now;
		currentPage = (currentPage + 1) % numPages;
	}
	if(now - backlightTime >= 30000) {
		backlightTime = now;
		lcd.noBacklight();
	}
	displayPage(currentPage);
}

void PagedLCD::setPage(byte page) {
	currentPage = page;
	if(currentPage >= numPages)
		currentPage = numPages - 1;
	lcd.backlight();
	backlightTime = millis();
	time = backlightTime;
}
