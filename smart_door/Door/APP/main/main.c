#include <avr/io.h>
#include <avr/delay.h>
#include "../../HAL/LCD/LCD.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../HAL/Keypad/keypad.h"
#include "../../HAL/Keypad/keypad_config.h"

int main ()
{
	u8 key;
	u8 mode;
	u32 Saved_Pass = 1234;
	u32 Reversed_Pass = 4321;
	u32 Get_Reversed_Pass = 0;     //Initialize the variable GET_reserved_pass
	u32 Temp_Pass = 0;
	u32 Comp_Pass =  0;
	u8 motor_steps[2] = {6,3};
	Set_GroupDir(PORT_C,0x0F);
	Set_GroupLevel(PORT_C,0xF0);
	LCD_Init ();
	Display_Str_Row_Col(0,2,"Welcome Home"); //sending a string to the LCD welcome home
	_delay_ms(500);
	while(1)
	{
		LCD_CLEAR();                                // clear the LCD
		Display_Str_Row_Col(0,2,"Choose a Mode");   //sending a string to the LCD choose a mode
		_delay_ms(400);
		LCD_CLEAR();
		Display_Str("1-Enter Password");
		Display_Str_Row_Col(1,0,"2-Change Password");
		mode = Keypad_GetPressedKey();            // move the data of Keypad_getpressedkey to the variable mode

		// wait the user to enter the password
		if ( mode == 1)
		{
			LCD_CLEAR();
			Display_Str("Password : ");
			for (u8 i = 0; i<4 ;i++)
			{
				Send_CMD(CURSOR_ON); // turn on the cursor
				_delay_ms(100);      // delay before sending another command
				Send_CMD(CURSOR_OFF);// turn off the cursor

				key = Keypad_GetPressedKey();
				if ((key>=0) && (key <=9))  // to make the password only numbers
				{
					Integer_TO_String (key);
					_delay_ms(200);
					Display_Str_Row_Col(0,11+i,"*");
				}
				else
				{
					LCD_CLEAR();         //clear the LCD
					Display_Str_Row_Col(0,1,"Invalid Input");
					_delay_ms(400);
					break;
				}
				// to write an integer number
				Comp_Pass += key;
				Comp_Pass = Comp_Pass * 10;
			}
			Comp_Pass = Comp_Pass / 10;
			_delay_ms(400);
			LCD_CLEAR();
			if (Saved_Pass == Comp_Pass)
			{
				Display_Str("Welcome Back");
				PORTC = (PORTC & 0xF0) | (motor_steps[1] & 0x0F);  // 90
				_delay_ms(2500);
				PORTC = (PORTC & 0xF0) | (motor_steps[0] & 0x0F);  //   0
				LCD_CLEAR();
				Comp_Pass = 0;
			}
			else if (Reversed_Pass == Comp_Pass)
			{
				Display_Str_Row_Col(0,1,"Calling  911");
				_delay_ms(1000);
				LCD_CLEAR();
				Comp_Pass = 0;
			}
			else
			{
				Display_Str_Row_Col(0,1,"Wrong Password");
				_delay_ms(500);
				LCD_CLEAR();
				Comp_Pass = 0;
			}
		}

		// for changing the Password
		else if (mode == 2)
		{
			LCD_CLEAR();
			Display_Str("Old Pass : ");
			for (u8 i = 0; i<4 ;i++)
			{
				Send_CMD(CURSOR_ON);
				_delay_ms(100);
				Send_CMD(CURSOR_OFF);
				key = Keypad_GetPressedKey();
				if ((key>=0) && (key <=9))
				{
					Integer_TO_String (key);
					_delay_ms(200);
					Display_Str_Row_Col(0,11+i,"*");
				}
				else
				{
					LCD_CLEAR();
					Display_Str_Row_Col(0,1,"Invalid Input");
					_delay_ms(400);
					break;
				}
				Comp_Pass += key;
				Comp_Pass = Comp_Pass * 10;
			}
			Comp_Pass = Comp_Pass / 10;
			_delay_ms(400);
			LCD_CLEAR();
			if (Saved_Pass == Comp_Pass)
			{

				Comp_Pass = 0;
				Saved_Pass = 0;
				Reversed_Pass = 0;
				Get_Reversed_Pass = 0;
				Display_Str("New Pass : ");
				Display_Str_Row_Col(1,0,"only Numbers");
				for (u8 i = 0; i<4 ;i++)
				{
					Send_CMD(CURSOR_ON);
					_delay_ms(100);
					Send_CMD(CURSOR_OFF);

					key = Keypad_GetPressedKey();
					if ((key>=0) && (key <=9))
					{
						Go_To_Row_Col(0,11+i);
						Integer_TO_String (key);
						_delay_ms(200);
						Display_Str_Row_Col(0,11+i,"*");
					}

					Saved_Pass += key;
					Saved_Pass = Saved_Pass * 10;
				}
				Saved_Pass = Saved_Pass / 10;
				Temp_Pass = Saved_Pass;
				while (Temp_Pass > 0)
				{
					Get_Reversed_Pass = Temp_Pass % 10;
					Reversed_Pass = (Reversed_Pass * 10) + Get_Reversed_Pass;
					Temp_Pass = Temp_Pass / 10;
				}
				_delay_ms(400);
				LCD_CLEAR();
				Display_Str("Password changed");
				_delay_ms(400);
				LCD_CLEAR();
			}
			else
			{
				Display_Str_Row_Col(0,1,"Wrong Password");
				_delay_ms(400);
				LCD_CLEAR();
				Comp_Pass = 0;
			}
		}
		else
		{
			LCD_CLEAR();
			Display_Str_Row_Col(0,1,"Invalid Input");
			_delay_ms(400);
		}
	}
}
