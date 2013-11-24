/*
 * SoldoSensors.h
 *
 *  Created on: 23. 11. 2013.
 *      Author: Dean
 */

#ifndef SOLDOSENSORS_H_
#define SOLDOSENSORS_H_

#include "Arduino.h"
#include "NamedSensor.h"
#include "NamedDHT11.h"
#include "NamedOneWireSensor.h"
#include "SoldoCommon.h"

#define SOLDO_SENSORS_COUNT 5
extern NamedSensor* soldoSensors[SOLDO_SENSORS_COUNT];

void initSensors();

#endif /* SOLDOSENSORS_H_ */
