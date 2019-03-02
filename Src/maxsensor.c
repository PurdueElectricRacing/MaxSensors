/*
 *  maxsensor.c
 *
 *  Created on: Feb 9, 2019
 *      Author: halowens
 */
#include "max1161x.h"
#include <math.h>
#include "maxsensor.h"

/**
 * @brief      Calculates the temperature of the Inline Flow Temp Sensor
 * @param      *tempSensor, Pointer to a sensor struct that defines the parameters of the specific sensor being read.
 */
uint8_t maxsensor_Inlineflow_Read(void * tempSensor)
{
  uint8_t status;
  uint16_t adcValue;
  float32_t vOut;
  float32_t resistance;
  uint16_t knownR = 10000; //Resistance of resistor in front of the flow Sensor

  status = MAX11615_ADC_Read(tempSensor->max, tempSensor->pin, adcValue);

  vOut = (adcvalue / 4095.0) * 4.73;
  resistance = (-knowR * vOut) / (vOut - 4.73);
  
  //Line of best fit calculated off of data in datasheet
  //Temperature = -26.689*ln(Resistance) + 272.279
  tmepSensor->value = -26.689 * log(resistance) + 272.279;
  
  return status;
}

/**
 * @brief      Calculates the distance of the shock pot between 0-100mm
 * @param      *strainSensor, Pointer to a sensor struct that defines the parameters of the specific sensor being read.
 */
uint8_t maxsensor_Straingauge_Read(void * strainSensor)
{
  //using shock pot with 100mm travel range
  uint8_t status;
  uint8_t vOut;
  uint8_t range = 100; //maximum travel distance of shock Pot 
  
  status = MAX11615_ADC_Read(strainSensor->max, strainSensor->pin, adcValue);
  strainSensor->value = (adcValue/4095.0) * range;

  return status;
}
