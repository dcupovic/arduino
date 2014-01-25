/*
 * DS1302Time.cpp
 *
 *  Created on: 25. 11. 2013.
 *      Author: Dean
 */

#include "DS1302Time.h"

DS1302 rtc(DS1302_RST, DS1302_DAT, DS1302_CLK);

void printDigits(Print &print, int digits) {
	// utility function for digital clock display: prints preceding colon and leading 0
	print.print(":");
	if (digits < 10)
		print.print('0');
	print.print(digits);
}

void digitalDateDisplay(Print& print) {
	print.print(day());
	print.print(".");
	print.print(month());
	print.print(".");
	print.print(year());
}

void digitalTimeDisplay(Print& print) {
	print.print(hour());
	printDigits(print, minute());
	printDigits(print, second());
}

void digitalClockDisplay(Print &print) {
	// digital clock display of the time
	digitalTimeDisplay(print);
	print.print(" ");
	digitalDateDisplay(print);
	print.println();
}

time_t getDS1302Time() {
	Time time;
	do {
		time = rtc.getTime();
		delay(100);
	} while (time.year < 2013);
	tmElements_t t;
	t.Day = time.date;
	t.Hour = time.hour;
	t.Minute = time.min;
	t.Month = time.mon;
	t.Second = time.sec;
	t.Wday = time.dow;
	t.Year = time.year - 1970;
	return makeTime(t);
}

void initTime() {
	setSyncProvider(getDS1302Time);
	//rtc.setDate(26, 11, 2013);
	//rtc.setTime(20,36,0);
//	Serial.println("//////////////////////////////////");
//	Serial.println(rtc.getTimeStr());
//	Serial.println(rtc.getDateStr());
//	Serial.println("//////////////////////////////////");
//	delay(1000);
//	Serial.println(rtc.getTimeStr());
//	Serial.println(rtc.getDateStr());
//	Serial.println("//////////////////////////////////");
//	delay(1000);
//	Serial.println(rtc.getTimeStr());
//	Serial.println(rtc.getDateStr());
//	Serial.println("//////////////////////////////////");
}

