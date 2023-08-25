/*
 * main.c
 *
 *  Created on: Aug 21, 2023
 *      Author: Menna
 */
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "LCD_config.h"
#include "LCD_interface.h"
#include "KPD_config.h"
#include "KPD_interface.h"
#include <util/delay.h>

int main()
{


		/* For LCD */

		DIO_VidSetPortDirection(LCD_DATA_PORT,Output);
		DIO_VidSetPinDirection(LCD_CTRL_PORT,Pin0,Output);
		DIO_VidSetPinDirection(LCD_CTRL_PORT,Pin1,Output);
		DIO_VidSetPinDirection(LCD_CTRL_PORT,Pin2,Output);


		/* Initialization */

		LCD_VidInit();
		KPD_VidInit();

		u16 Local_u8Number1 , Local_u8Number2  , Local_u8Check1 , Local_u8Check2 ,Local_u16Result=0;
		u8 Local_u8Operation;
		f32 Local_f32Result=0;
		u16 Local_f32Flag;

		LCD_VidSendString("Welcome to mini Calculator");
		_delay_ms(1000);
		LCD_VidSendCommand(1);

		while(1)
		{
			Local_f32Flag=0;
			Local_u8Check1=0;
			Local_u8Check2=0;
			Local_u8Number1=KPD_NO_PRESSED_KEY;
			Local_u8Number2=KPD_NO_PRESSED_KEY;


			Local_u8Number1= KPD_u8GetPressedKey();
			while(KPD_NO_PRESSED_KEY==Local_u8Number1 || (Local_u8Number1!='+' && Local_u8Number1!='-' && Local_u8Number1!='*' && Local_u8Number1!='/'))
			{
				if(KPD_NO_PRESSED_KEY==Local_u8Number1)
				{
				Local_u8Number1= KPD_u8GetPressedKey();
				}
				else
				{
					Local_u8Check1*=10;
					Local_u8Check1+=Local_u8Number1;
					LCD_VidSendNumber(Local_u8Number1);
					Local_u8Number1=KPD_NO_PRESSED_KEY;
				}
			}

			Local_u8Operation = (u8)Local_u8Number1;
			LCD_VidSendData(Local_u8Operation);

			Local_u8Number2= KPD_u8GetPressedKey();
			while(KPD_NO_PRESSED_KEY==Local_u8Number2 ||(Local_u8Number2!='='))
			{
					if(KPD_NO_PRESSED_KEY==Local_u8Number2)
					{
							Local_u8Number2= KPD_u8GetPressedKey();
					}
					else
					{
							Local_u8Check2*=10;
							Local_u8Check2+=Local_u8Number2;
							LCD_VidSendNumber(Local_u8Number2);
							Local_u8Number2=KPD_NO_PRESSED_KEY;
					}
			}


			switch(Local_u8Operation)
			{
			case '+': Local_u16Result = Local_u8Check1+Local_u8Check2;   break;
			case '-': Local_u16Result = Local_u8Check1-Local_u8Check2;   break;
			case '*': Local_u16Result = Local_u8Check1*Local_u8Check2;   break;
			case '/':
						if (Local_u8Check1 % Local_u8Check2 == 0)
						{
							Local_u16Result = Local_u8Check1 / Local_u8Check2;
						}
						else
						{
							Local_f32Flag = 1;
							Local_f32Result = (f32) Local_u8Check1 / Local_u8Check2;
							Local_u16Result = Local_u8Check1 / Local_u8Check2;
							Local_f32Result = 10 * (Local_f32Result - Local_u16Result);
						}
																		  break;
			}


			LCD_VidSendData('=');

			if(Local_f32Flag==0)
			{
				LCD_VidSendNumber(Local_u16Result);
			}
			else
			{
				if(Local_u16Result==1)
				{
					LCD_VidSendData('0');
				}
				else
				{
					LCD_VidSendNumber(Local_u16Result);
				}

				LCD_VidSendData('.');
				LCD_VidSendNumber(Local_f32Result);

			}

			Local_u8Number1=KPD_NO_PRESSED_KEY;
			while(KPD_NO_PRESSED_KEY==Local_u8Number1 || 'C' !=Local_u8Number1 )
			{
				Local_u8Number1=KPD_u8GetPressedKey();
			}

			LCD_VidSendCommand(1); //clear display

		}

}
