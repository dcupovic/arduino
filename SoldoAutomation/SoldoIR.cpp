/*
 * SoldoIR.cpp
 *
 *  Created on: 25. 11. 2013.
 *      Author: Dean
 */

#include "SoldoIR.h"

IRrecv irrecv(IR_PIN);
decode_results results;

void initIR() {
	irrecv.enableIRIn();
}

void loopIR() {
	if (irrecv.decode(&results)) {
		Serial.println(results.value, HEX);
		switch (results.value) {
		case 0xFF6897:
//			Serial.println(" 0              ");
			break;

		case 0xFF30CF:
//			Serial.println(" 1              ");
			setLCDPage(0);
			break;

		case 0xFF18E7:
//			Serial.println(" 2              ");
			setLCDPage(1);
			break;

		case 0xFF7A85:
//			Serial.println(" 3              ");
			setLCDPage(2);
			break;

		case 0xFF10EF:
//			Serial.println(" 4              ");
			setLCDPage(3);
			break;

		case 0xFF38C7:
//			Serial.println(" 5              ");
			break;

		case 0xFF5AA5:
//			Serial.println(" 6              ");
			break;

		case 0xFF42BD:
//			Serial.println(" 7              ");
			break;

		case 0xFF4AB5:
//			Serial.println(" 8              ");
			break;

		case 0xFF52AD:
//			Serial.println(" 9              ");
			break;

		case 0xFFE01F:
//		    Serial.println(" VOL-           ");
			if(getCurrentLCDSelection() == 1) soldoRelays[0]->Off();
			if(getCurrentLCDSelection() == 2) soldoRelays[1]->Off();
			break;

		case 0xFFA857:
			//Serial.println(" VOL+           ");
			if(getCurrentLCDSelection() == 1) soldoRelays[0]->On();
			if(getCurrentLCDSelection() == 2) soldoRelays[1]->On();
			break;

		case 0xFF22DD:
			//Serial.println(" PREV           ");
			LCDselectPrevious();
			break;

		case 0xFF02FD:
			//Serial.println(" NEXT           ");
			LCDselectNext();
			break;
//		default:
//			Serial.println(" other button   ");

		}
		irrecv.resume(); // Receive the next value
	}
}
