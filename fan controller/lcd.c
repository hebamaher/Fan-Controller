#include "common_macros.h"
#include "lcd.h"
#include "gpio.h"
#include <util/delay.h>

void LCD_init(void){
	GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);
	_delay_ms(20);

#if(LCD_MODE == 8)
	GPIO_setupPortDirection(LCD_DP_PORT_ID, PORT_OUTPUT);

	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);

#elif(LCD_MODE == 4)
	GPIO_setupPinDirection(LCD_DP_PORT_ID, LCD_DP4_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DP_PORT_ID, LCD_DP5_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DP_PORT_ID, LCD_DP6_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DP_PORT_ID, LCD_DP7_PIN_ID, PIN_OUTPUT);

	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);
#endif

	LCD_sendCommand(LCD_CURSOR_OFF);
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}

void LCD_sendCommand(uint8 command){
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

#if(LCD_MODE == 8)
	GPIO_writePort(LCD_DP_PORT_ID, command);

#elif(LCD_MODE == 4)
	GPIO_writePin(LCD_DP_PORT_ID, LCD_DP4_PIN_ID, GET_BIT(command,4));
	GPIO_writePin(LCD_DP_PORT_ID, LCD_DP5_PIN_ID, GET_BIT(command,5));
	GPIO_writePin(LCD_DP_PORT_ID, LCD_DP6_PIN_ID, GET_BIT(command,6));
	GPIO_writePin(LCD_DP_PORT_ID, LCD_DP7_PIN_ID, GET_BIT(command,7));

	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

	GPIO_writePin(LCD_DP_PORT_ID, LCD_DP4_PIN_ID, GET_BIT(command,0));
	GPIO_writePin(LCD_DP_PORT_ID, LCD_DP5_PIN_ID, GET_BIT(command,1));
	GPIO_writePin(LCD_DP_PORT_ID, LCD_DP6_PIN_ID, GET_BIT(command,2));
	GPIO_writePin(LCD_DP_PORT_ID, LCD_DP7_PIN_ID, GET_BIT(command,3));

#endif

	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
}


void LCD_displayCharacter(uint8 character){
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

#if(LCD_MODE == 8)
	GPIO_writePort(LCD_DP_PORT_ID, character);

#elif(LCD_MODE == 4)
	GPIO_writePin(LCD_DP_PORT_ID, LCD_DP4_PIN_ID, GET_BIT(character,4));
	GPIO_writePin(LCD_DP_PORT_ID, LCD_DP5_PIN_ID, GET_BIT(character,5));
	GPIO_writePin(LCD_DP_PORT_ID, LCD_DP6_PIN_ID, GET_BIT(character,6));
	GPIO_writePin(LCD_DP_PORT_ID, LCD_DP7_PIN_ID, GET_BIT(character,7));

	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

	GPIO_writePin(LCD_DP_PORT_ID, LCD_DP4_PIN_ID, GET_BIT(character,0));
	GPIO_writePin(LCD_DP_PORT_ID, LCD_DP5_PIN_ID, GET_BIT(character,1));
	GPIO_writePin(LCD_DP_PORT_ID, LCD_DP6_PIN_ID, GET_BIT(character,2));
	GPIO_writePin(LCD_DP_PORT_ID, LCD_DP7_PIN_ID, GET_BIT(character,3));
#endif

	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
}


void LCD_displayString(uint8* str){
	int i=0;
	while(str[i] != '\0'){
		LCD_displayCharacter(str[i]);
		i++;
	}
}

void LCD_moveCursor(uint8 row,uint8 col)
{
	uint8 lcd_memory_address;

	/* Calculate the required address in the LCD DDRAM */
	switch(row)
	{
		case 0:
			lcd_memory_address=col;
				break;
		case 1:
			lcd_memory_address=col+0x40;
				break;
		case 2:
			lcd_memory_address=col+0x10;
				break;
		case 3:
			lcd_memory_address=col+0x50;
				break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_moveCursor(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}

void LCD_intgerToString(int data)
{
   char buff[16]; /* String to hold the ascii result */
   itoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
   LCD_displayString(buff); /* Display the string */
}

void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* Send clear display command */
}

