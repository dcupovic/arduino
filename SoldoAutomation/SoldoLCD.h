/*
 * SoldoLCD.h
 *
 *  Created on: 25. 11. 2013.
 *      Author: Dean
 */

#ifndef SOLDOLCD_H_
#define SOLDOLCD_H_

#include "LCD/PagedLCD.h"
#include "LCD.h"
#include "sensors/NamedSensor.h"
#include "time/DS1302Time.h"

class SoldoLCD: public PagedLCD {
private:
	NamedSensor** sensors;
protected:
	void displayPage(byte page);
	void goto1of2();
	void goto2of2();
	void goto1of4();
	void goto2of4();
	void goto3of4();
	void goto4of4();
	void printSpaces();
public:
	SoldoLCD(LCD& lcd, NamedSensor** sensors);
	virtual ~SoldoLCD();
};

#endif /* SOLDOLCD_H_ */
