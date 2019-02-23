/*
 * InlineFlowTempSensor.h
 *
 *  Created on: Feb 9, 2019
 *      Author: halowens
 */

#ifndef MAXSENSOR_H_
#define MAXSENSOR_H_

#include "max1161x.h"


typedef struct {
	uint8_t pin; // Pin on the MAX Chip
	MAX11615* max; //When were using both chips this can define which one is being used
	uint16_t value; // holds the value of sensor is updated by calling the function below
	uint8_t (*read)(struct sensor*); //Should be called to get sensor value
}sensor;

uint8_t INLINETEMP_Read(sensor*);

#endif /* MAXSENSOR_H_ */
