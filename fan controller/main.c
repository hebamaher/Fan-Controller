/*
 * main.c
 *
 *  Created on: Oct 12, 2023
 *      Author: Eng Heba
 */


#include "adc.h"
#include "lcd.h"
#include "lm35_sensor.h"
#include "pwm.h"
#include "dc_motor.h"


int main(void){
	uint8 temp_value = 0, prev_value = 0;

	LCD_init();
	DcMotor_Init();
	DcMotor_Rotate(STOP, 0);

	ADC_ConfigType ADC_Configurations = {INTERNAL_VREF, ADC_F_CPU_8};
	ADC_init(&ADC_Configurations);

	while(1){
		temp_value = LM35_getTemperature();
		if(temp_value != prev_value){ //to prevent repetition of same value on lcd

			if(temp_value < 30){

				LCD_clearScreen();

				DcMotor_Rotate(STOP, 0);

				LCD_displayString("FAN IS OFF");
			}
			else if(temp_value >= 30 && temp_value < 60){

				LCD_clearScreen();

				DcMotor_Rotate(CW, 25);

				LCD_displayString("FAN IS ON");
				LCD_moveCursor(1,0);
				LCD_displayString("TEMP =    C");
				LCD_moveCursor(1,7);
				LCD_intgerToString(temp_value);

			}
			else if(temp_value >= 60 && temp_value < 90){

				LCD_clearScreen();

				DcMotor_Rotate(CW, 50);

				LCD_displayString("FAN IS ON");
				LCD_moveCursor(1,0);
				LCD_displayString("TEMP =    C");
				LCD_moveCursor(1,7);
				LCD_intgerToString(temp_value);
			}
			else if(temp_value >= 90 && temp_value < 120){

				LCD_clearScreen();

				DcMotor_Rotate(CW, 75);

				LCD_displayString("FAN IS ON");
				LCD_moveCursor(1,0);
				LCD_displayString("TEMP =    C");
				LCD_moveCursor(1,7);
				LCD_intgerToString(temp_value);
			}
			else{

				LCD_clearScreen();

				DcMotor_Rotate(CW, 100);

				LCD_displayString("FAN IS ON");
				LCD_moveCursor(1,0);
				LCD_displayString("TEMP =    C");
				LCD_moveCursor(1,7);
				LCD_intgerToString(temp_value);
			}
			prev_value = temp_value;
		}


	}
}
