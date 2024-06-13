/*
 * pwm.c
 *
 *  Created on: Oct 13, 2023
 *      Author: Eng Heba
 */


#include "pwm.h"
#include "gpio.h"
#include <avr/io.h>
#include "common_macros.h"


TIMER0_WGM waveform = FastPWM;
TIMER0_COM_PWM com_pwm = NON_INV;
TIMER0_ClockType prescaler = TIMER0_F_CPU_8;

//struct *Config_Ptr;
void PWM_Timer0_Start(uint8 duty_cycle){
	TCNT0 = 0;

	//OCR0 = duty_cycle;
	uint8 speed = (((float)duty_cycle/100)*255);

	OCR0  = speed; // Set Compare Value

	GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);

	if(waveform == WGM_NORMAL){
		CLEAR_BIT(TCCR0, WGM00);
		CLEAR_BIT(TCCR0, WGM01);
	}
	else if(waveform == PhaseCorrect){
		SET_BIT(TCCR0, WGM00);
		CLEAR_BIT(TCCR0, WGM01);
	}
	else if(waveform == CTC	){
		CLEAR_BIT(TCCR0, WGM00);
		SET_BIT(TCCR0, WGM01);
	}
	else if(waveform == FastPWM){
		SET_BIT(TCCR0, WGM00);
		SET_BIT(TCCR0, WGM01);
	}

	if(com_pwm == COM_NORMAL){
		CLEAR_BIT(TCCR0, COM00);
		CLEAR_BIT(TCCR0, COM01);
	}
	else if(com_pwm == PWM_RESERVED){
		SET_BIT(TCCR0, COM00);
		CLEAR_BIT(TCCR0,COM01);
	}
	else if(com_pwm == NON_INV){
		CLEAR_BIT(TCCR0, COM00);
		SET_BIT(TCCR0, COM01);
	}
	else if(com_pwm == INV){
		SET_BIT(TCCR0, COM00);
		SET_BIT(TCCR0, COM01);
	}

	TCCR0 = (TCCR0 & 0b11111000) | prescaler;
}
