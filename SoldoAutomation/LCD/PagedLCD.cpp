/*
 * PagedLCD.cpp
 *
 *  Created on: 25. 11. 2013.
 *      Author: Dean
 */

#include "PagedLCD.h"

PagedLCD::PagedLCD(LCD& lcd, byte numPages, byte numSelections) :
		lcd(lcd), numPages(numPages), currentPage(0), numSelections(
				numSelections), currentSelection(0) {
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
	if(now - selectionTime >= 10000) {
		selectionTime = now;
		currentSelection = 0;
	}
	if(now - backlightTime >= 30000) {
		backlightTime = now;
		lcd.noBacklight();
	}
	displayPage(currentPage, currentSelection);
}

void PagedLCD::setPage(byte page) {
	currentPage = page;
	if(currentPage >= numPages)
		currentPage = numPages - 1;
	lcd.backlight();
	backlightTime = millis();
	time = backlightTime;
}

void PagedLCD::selectNext() {
	if (numSelections > 0) {
		++currentSelection;
		if (currentSelection > numSelections)
			currentSelection = 1;
		updatePageForSelection();
	}
}

void PagedLCD::updatePageForSelection() {
	byte page = getPageForSelection(currentSelection);
	if(page != 255)
		setPage(page);
}

byte PagedLCD::getPageForSelection(byte selection) {
	return 255;
}

void PagedLCD::selectPrevious() {
	if (numSelections > 0) {
		if(currentSelection > 0)
			--currentSelection;
		if (currentSelection < 1)
			currentSelection = numSelections;
		updatePageForSelection();
	}
}

byte PagedLCD::getCurrentSelection() {
	return currentSelection;
}
