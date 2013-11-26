/*
 * DS1302Time.cpp
 *
 *  Created on: 25. 11. 2013.
 *      Author: Dean
 */

#include "DS1302Time.h"

DS1302 rtc(DS1302_RST, DS1302_DAT, DS1302_CLK);

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year());
  Serial.println();
}

time_t getDS1302Time() {
	Time time;
	do {
		time = rtc.getTime();
		Serial.println("//////////////////////////////////");
		Serial.println(rtc.getTimeStr(FORMAT_SHORT));
		Serial.println("//////////////////////////////////");
		delay(100);
	} while (time.year < 2013);
	tmElements_t t;
	t.Day = time.date;
	t.Hour = time.hour;
	t.Minute = time.min;
	t.Month = time.mon;
	t.Second = time.sec;
	t.Wday = time.dow;
	t.Year = time.year;
	return makeTime(t);
}

void initTime() {
	setSyncProvider(getDS1302Time);
	Serial.println("//////////////////////////////////");
	Serial.println(rtc.getTimeStr());
	Serial.println(rtc.getDateStr());
	Serial.println("//////////////////////////////////");
}

