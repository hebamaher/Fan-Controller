/*
 * adc.h
 *
 *  Created on: Oct 9, 2023
 *      Author: Eng Heba
 */

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

#define ADC_REF_VOLT         2.56
#define ADC_MAXIMUM_VALUE    1023

typedef enum{
	AREF, AVCC, ADC_RESERVED, INTERNAL_VREF
}ADC_ReferenceVolatge;

typedef enum{
	ADC_F_CPU, ADC_F_CPU_2, ADC_F_CPU_4, ADC_F_CPU_8, ADC_F_CPU_16, ADC_F_CPU_32, ADC_F_CPU_64, ADC_F_CPU_128
}ADC_Prescaler;

typedef struct{
	ADC_ReferenceVolatge ref_volt ;
	ADC_Prescaler prescaler ;
}ADC_ConfigType;

void ADC_init(const ADC_ConfigType * ADC_Config_Ptr);
uint16 ADC_readChannel(uint8 ch_num);

#endif /* ADC_H_ */
