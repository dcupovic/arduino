/*
 * PersistentRelay.h
 *
 *  Created on: 26. 11. 2013.
 *      Author: Dean
 */

#ifndef PERSISTENTRELAY_H_
#define PERSISTENTRELAY_H_

#include "Arduino.h"
#include "EEPROM.h"
#include "Relay.h"

class PersistentRelay: public Relay {
private:
	uint16_t address;
	bool hasValidSentinel();
	void writeSentinel();
	bool readState();
	void writeState(bool state);
public:
	PersistentRelay(uint16_t address, byte pin);
	virtual ~PersistentRelay();
	void On();
	void Off();
};

#endif /* PERSISTENTRELAY_H_ */
