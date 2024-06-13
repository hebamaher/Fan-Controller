/*
 * adc.c
 *
 *  Created on: Oct 9, 2023
 *      Author: Eng Heba
 */

#include "adc.h"
#include "common_macros.h"
#include <avr/io.h>

void ADC_init(const ADC_ConfigType * ADC_Config_Ptr){
	if(ADC_Config_Ptr -> ref_volt == AREF){
		CLEAR_BIT(ADMUX,REFS0);
		CLEAR_BIT(ADMUX,REFS1);
	}
	else if(ADC_Config_Ptr -> ref_volt == AVCC){
		SET_BIT(ADMUX,REFS0);
		CLEAR_BIT(ADMUX,REFS1);
	}
	else if(ADC_Config_Ptr -> ref_volt == ADC_RESERVED){
		CLEAR_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
	}
	else if(ADC_Config_Ptr -> ref_volt == INTERNAL_VREF){
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
	}

	SET_BIT(ADCSRA,ADEN); //adc enable
	CLEAR_BIT(ADCSRA,ADIE); //interrupt disable

	ADCSRA = (ADCSRA & 0xF8) | ADC_Config_Ptr -> prescaler;
}


uint16 ADC_readChannel(uint8 ch_num){
	ch_num &= 0x07;
	ADMUX = (ADMUX & 0b11100000) | (ADMUX | ch_num);
	SET_BIT(ADCSRA,ADSC); //start conversion
	while(BIT_IS_CLEAR(ADCSRA,ADIF)){
		//polling until conversion ends
	}
	SET_BIT(ADCSRA,ADIF); //clear end of conversion flag
	return ADC;

}
