/*
 * InlineFlowTempSensor.c
 *
 *  Created on: Feb 9, 2019
 *      Author: halowens
 */
#include "MAX11615.h"
#include <math.h>
#include <MAXsensor.h>

/**
 * @brief      Calculates the temperature of the Inline Flow Temp Sensor
 * @param      *inlineT, Pointer to a sensor struct that defines the parameters of the specific sensor being read.
 */
uint8_t INLINETEMP_Read(sensor* inlineT)
{
	uint8_t status;
	uint16_t adcValue;
	float vOut;
	float resistance;
	float buffer;
	uint16_t knownR = 10000;

	status = MAX11615_ADC_Read(inlineT->max, inlineT->pin, adcValue);

	/*
	 * This takes the read voltage value and calculates the resistance of the sensor based
	 * off the fact that there is a 10k ohm resistor in front of the sensor like in the datasheet
	 * No idea if it works but you need resistance to get the temperature value
	 */
	vOut = (adcValue/2048) * 5.0;
	buffer = (5/vOut) - 1;
	resistance = knownR * buffer;

	//Temperature = -26.689*ln(x) + 272.279
	inlineT->value = -26.689 * log(resistance) + 272.279;
	return status;

}

