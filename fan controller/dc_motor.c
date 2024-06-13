/*
 * dc_motor.c
 *
 *  Created on: Oct 12, 2023
 *      Author: Eng Heba
 */


#include "dc_motor.h"
#include "gpio.h"
#include "pwm.h"



void DcMotor_Init(void){
	GPIO_setupPinDirection(DcMotor_OUTPUT_PORT_ID, DcMotor_OUTPUT1_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DcMotor_OUTPUT_PORT_ID, DcMotor_OUTPUT2_PIN_ID, PIN_OUTPUT);

	GPIO_writePin(DcMotor_OUTPUT_PORT_ID, DcMotor_OUTPUT1_PIN_ID, LOGIC_LOW); //intially motor at stop state
	GPIO_writePin(DcMotor_OUTPUT_PORT_ID, DcMotor_OUTPUT2_PIN_ID, LOGIC_LOW);

}
void DcMotor_Rotate(DcMotor_State state,uint8 speed){

	if (STOP == state)
	{
		GPIO_writePin(DcMotor_OUTPUT_PORT_ID, DcMotor_OUTPUT1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DcMotor_OUTPUT_PORT_ID, DcMotor_OUTPUT2_PIN_ID, LOGIC_LOW);
	}
	else if (CW == state)
	{
		GPIO_writePin(DcMotor_OUTPUT_PORT_ID, DcMotor_OUTPUT1_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(DcMotor_OUTPUT_PORT_ID, DcMotor_OUTPUT2_PIN_ID, LOGIC_LOW);
		PWM_Timer0_Start(speed);
	}

}
