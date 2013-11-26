/*
 * SoldoLCDImplementation.h
 *
 *  Created on: 25. 11. 2013.
 *      Author: Dean
 */

#ifndef SOLDOLCDIMPLEMENTATION_H_
#define SOLDOLCDIMPLEMENTATION_H_

#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "SoldoLCD.h"
#include "SoldoSensors.h"

void initLCD();
void loopLCD();
void setLCDPage(byte page);
void LCDselectNext();
void LCDselectPrevious();
byte getCurrentLCDSelection(); //zero if none selected


#endif /* SOLDOLCDIMPLEMENTATION_H_ */
