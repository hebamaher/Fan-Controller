/*
 * dc_motor.h
 *
 *  Created on: Oct 12, 2023
 *      Author: Eng Heba
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"


#define DcMotor_OUTPUT_PORT_ID   PORTB_ID
#define DcMotor_OUTPUT1_PIN_ID   PIN0_ID
#define DcMotor_OUTPUT2_PIN_ID   PIN1_ID
#define DcMotor_ENABLE_PIN_ID   PIN3_ID

//#define DcMotor_OUTPUT_PORT_ID   PORTD_ID
//#define DcMotor_OUTPUT1_PIN_ID   PIN0_ID
//#define DcMotor_OUTPUT2_PIN_ID   PIN1_ID

#define DcMotor_OUTPUT_PORT      PORTB

typedef enum{
	STOP, CW, ACW
}DcMotor_State;

/*typedef struct{
	DcMotor_State state;
	uint8 speed;
}DcMotor_ConfigType;*/

void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DC_MOTOR_H_ */
