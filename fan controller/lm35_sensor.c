/*
 * lm35_sensor.c
 *
 *  Created on: Oct 9, 2023
 *      Author: Eng Heba
 */

#include "lm35_sensor.h"
#include "adc.h"
#include <util/delay.h>

uint8 LM35_getTemperature(void){
	uint8 temp = 0;
	uint16 adc_value = 0;
	adc_value = ADC_readChannel(SENSOR_CHANNEL_ID); //output of adc stored in adc reg that is being returned from this func

	temp = (uint8)(((uint32)adc_value * SENSOR_MAX_TEMPERATURE * ADC_REF_VOLT)/(SENSOR_MAX_VOLT * ADC_MAXIMUM_VALUE)); //using adc value in temp calc
	return temp;
}
