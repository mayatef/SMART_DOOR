#include "LCD.h"
#include <avr/delay.h>
#include <stdio.h>
/*Function Definition*/

void LCD_Init (void)			                 	// initialization of LCD
{
	Set_GroupDir (LCD_DATA_PORT_DIR,0xFF);			//Set PORTB as o/p port
	LCD_CTRL_PORT_DIR = (1<<EN) | (1<<RS) | (1<<RW);//Set RS, RW, ENABLE pins as o/p port
	_delay_ms(50); 							     	//Delay before initialization FUNCTION
	Send_CMD (TWO_LINE_LCD_EIGHT_BIT_MODE);		    //Set LCD mode as 8-bit mode, 2-lines, 5*8 Dots
	_delay_ms(1);
	Send_CMD (CURSOR_OFF);					     	//MAKE Cursor off
	_delay_ms(1);
	Send_CMD (CLEAR_COMMAND);				    	//Clear LCD at initialization
	_delay_ms(2);
}

void Send_CMD (u8 cmd)				// Function For Sending commands to LCD
{
	CLEAR_BIT(LCD_CTRL_PORT, RS);	//clear RS Pin (Command Instruction)
	CLEAR_BIT(LCD_CTRL_PORT, RW);	//clear RW Pin (Write Mood)
	_delay_ms(1);					//Delay until Enable Start
	SET_BIT(LCD_CTRL_PORT, EN);		//Enable LCD
	_delay_ms(1);					//Delay until sending commands
	LCD_DATA_PORT = cmd; 			//Send command to data pins
	_delay_ms(1);					//Delay until data sending is finished
	CLEAR_BIT(LCD_CTRL_PORT, EN);	//Disable LCD
}

void Send_DATA (u8 data)			// Function for sending data to LCD
{
	SET_BIT(LCD_CTRL_PORT, RS);		//set RS Pin (Command Instruction)
	CLEAR_BIT(LCD_CTRL_PORT, RW);	//clear RW Pin (Write Mood)
	_delay_ms(1);					//Delay until Enable Start
	SET_BIT(LCD_CTRL_PORT, EN);		//Enable LCD
	_delay_ms(1);					//Delay until Enable Start
	LCD_DATA_PORT = data; 			//Send data to data pins
	_delay_ms(1);					//Delay until data sending is finished
	CLEAR_BIT(LCD_CTRL_PORT, EN);	//Disable LCD
}

void Display_Str (const u8 *str)	// Function to display string on LCD
{
	u8 i=0;
	while (str[i] != '\0')
	{
		Send_DATA (str[i]);
		i++;
	}
}

void Go_To_Row_Col (u8 row, u8 col)	// Function for moving to a specific column and row on LCD
{
	u8 Address;
	switch (row)
	{
	case 0:
		Address = col;
		break;
	case 1:
		Address = col + 0x40;
		break;
	case 2:
		Address = col + 0x10;
		break;
	case 3:
		Address = col + 0x50;
		break;
	}
	Send_CMD (Address | SET_CURSOR_LOCATION); //To move cursor to specific Address location
}

void LCD_CLEAR (void)
{
	Send_CMD (CLEAR_COMMAND); //clearing the LCD
}

void Display_Str_Row_Col (u8 row, u8 col, const u8 *str)	//Display string at specified row and column
{
	Go_To_Row_Col (row,col);
	Display_Str (str);
}

void Integer_TO_String (u8 value)	// Display an integer number on the screen
{
	u8 number_str[30];
	itoa (value, number_str, 10); // convert integer number to character string
	Display_Str (number_str);
}
