/*
 * PersistentRelay.cpp
 *
 *  Created on: 26. 11. 2013.
 *      Author: Dean
 */

#include "PersistentRelay.h"

#define SENTINEL_START 0x55
#define SENTINEL_END 0xAA

PersistentRelay::PersistentRelay(uint16_t address, byte pin): address(address), Relay(pin){
	// TODO Auto-generated constructor stub
	if(hasValidSentinel()) {
		if(readState())
			On();
		else
			Off();
	} else {
		writeSentinel();
		Off();
	}
}

bool PersistentRelay::hasValidSentinel() {
	if(EEPROM.read(address) != SENTINEL_START)
		return false;
	if(EEPROM.read(address + 2) != SENTINEL_END)
		return false;
	return true;
}

void PersistentRelay::writeSentinel() {
	EEPROM.write(address, SENTINEL_START);
	EEPROM.write(address + 2, SENTINEL_END);
}

bool PersistentRelay::readState() {
	return EEPROM.read(address + 1) != 0;
}

void PersistentRelay::writeState(bool state) {
	EEPROM.write(address + 1, state ? 1 : 0);
}

PersistentRelay::~PersistentRelay() {
	// TODO Auto-generated destructor stub
}

void PersistentRelay::On() {
	Relay::On();
	writeState(true);
}

void PersistentRelay::Off() {
	Relay::Off();
	writeState(false);
}
