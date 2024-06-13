/*
 * pwm.h
 *
 *  Created on: Oct 13, 2023
 *      Author: Eng Heba
 */

#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"

 typedef enum{
	WGM_NORMAL, PhaseCorrect, CTC, FastPWM
}TIMER0_WGM;

typedef enum{
	COM_NORMAL, PWM_RESERVED, NON_INV, INV
}TIMER0_COM_PWM;

typedef enum{
	TIMER0_NO_CLOCK, TIMER0_F_CPU_CLOCK, TIMER0_F_CPU_8, TIMER0_F_CPU_64, TIMER0_F_CPU_256, TIMER0_F_CPU_1024, TIMER0_External_FALLING, TIMER0_External_RISING
}TIMER0_ClockType;


//TIMER0_WGM waveform = FastPWM;



void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_H_ */
