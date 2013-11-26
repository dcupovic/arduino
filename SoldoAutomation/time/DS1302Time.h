/*
 * DS1302Time.h
 *
 *  Created on: 25. 11. 2013.
 *      Author: Dean
 */

#ifndef DS1302TIME_H_
#define DS1302TIME_H_
#include "Time/Time.h"
#include "DS1302.h"
#include "../SoldoCommon.h"
#include "Print.h"

void initTime();
void digitalClockDisplay(Print &print);
void digitalDateDisplay(Print& print);
void digitalTimeDisplay(Print& print);


#endif /* DS1302TIME_H_ */
