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
	byte numPages, currentPage;
	unsigned long time, backlightTime;
protected:
	LCD& lcd;
	virtual void displayPage(byte page) = 0;
public:
	PagedLCD(LCD& lcd, byte numPages);
	virtual ~PagedLCD();
	void display();
	void setPage(byte page);
};

#endif /* PAGEDLCD_H_ */
