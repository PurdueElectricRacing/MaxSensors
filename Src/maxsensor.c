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
uint8_t maxsensor_Inlineflow_Read(void * tempSensor_temp)
{
  sensor_t * tempSensor = (sensor_t *) tempSensor_temp;
  uint8_t status;
  uint16_t adcValue;
  float vOut;
  float resistance;
  uint16_t knownR = FLOW_SPEED_RESISTOR_OHM; //Resistance of resistor in front of the flow Sensor

  status = max1161x_ADC_Read(tempSensor->max, tempSensor->pin, &adcValue);

  vOut = (adcValue / 4095.0) * 4.73;
  resistance = (-knownR * vOut) / (vOut - 4.73);

  //Line of best fit calculated off of data in datasheet
  //Temperature = -26.689*ln(Resistance) + 272.279
  tempSensor->value = -26.689 * log(resistance) + 272.279;

  return status;
}

/**
 * @brief      Calculates the distance of the shock pot between 0-100mm
 * @param      *strainSensor, Pointer to a sensor struct that defines the parameters of the specific sensor being read.
 */
uint8_t maxsensor_Straingauge_Read(void * strainSensor_temp)
{
  sensor_t * strainSensor = (sensor_t *) strainSensor_temp;
  uint8_t status;
  uint16_t adcValue;
  uint8_t range = 100; //maximum travel distance of shock Pot

  status = max1161x_ADC_Read(strainSensor->max, strainSensor->pin, &adcValue);
  strainSensor->value = (adcValue/4095.0) * range;

  return status;
}
