/*
 * PagedLCD.h
 *
 *  Created on: 25. 11. 2013.
 *      Author: Dean
 */

#ifndef PAGEDLCD_H_
#define PAGEDLCD_H_

#include "LCD.h"

class PagedLCD {
private:
	byte numPages, currentPage, numSelections, currentSelection;
	unsigned long time, backlightTime, selectionTime;
	void updatePageForSelection();
protected:
	LCD& lcd;
	virtual void displayPage(byte page, byte selection) = 0; //selection = 1..numSelections, 0 if none selected
	virtual byte getPageForSelection(byte selection);
public:
	PagedLCD(LCD& lcd, byte numPages, byte numSelections);
	virtual ~PagedLCD();
	void display();
	void setPage(byte page);
	void selectNext();
	void selectPrevious();
	byte getCurrentSelection();
};

#endif /* PAGEDLCD_H_ */
