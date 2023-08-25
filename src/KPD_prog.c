#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "KPD_config.h"
#include "KPD_interface.h"
#include <util/delay.h>


u8 KPD_u8GetPressedKey(void)
{
	//value if button is not pressed
	u8 Local_u8_Pressed_Key = KPD_NO_PRESSED_KEY;

	//Counters for loop
	u8 Local_u8_Column_Counter , Local_u8_Row_Counter;

	//variable for pin state
	u8 Local_u8_Pin_State;

	//Keypad Values *** static -> stored in .segment
	static u8 Local_u8_Kpd_Arr[ROW_NUM][COLUMN_NUM]=KPD_ARR_VAL;

	//Key column array
	static u8 Local_u8_Kpd_Column_Arr[COLUMN_NUM]={KPD_COLUMN_0,KPD_COLUMN_1,KPD_COLUMN_2,KPD_COLUMN_3};

	//key row array
	static u8 Local_u8_Kpd_Row_Arr[ROW_NUM]={KPD_ROW_0,KPD_ROW_1,KPD_ROW_2,KPD_ROW_3};

	for(Local_u8_Column_Counter=0;Local_u8_Column_Counter<COLUMN_NUM;Local_u8_Column_Counter++)
	{
		//activate current column
		DIO_VidSetPinValue(KPD_PORT,Local_u8_Kpd_Column_Arr[Local_u8_Column_Counter],PinLow);
		//read current row
		for(Local_u8_Row_Counter=0;Local_u8_Row_Counter<ROW_NUM;Local_u8_Row_Counter++)
		{
			DIO_VidGetPinValue(KPD_PORT,Local_u8_Kpd_Row_Arr[Local_u8_Row_Counter],&Local_u8_Pin_State);
			//check if key is pressed
			if(Local_u8_Pin_State==PinLow)
			{
				Local_u8_Pressed_Key=Local_u8_Kpd_Arr[Local_u8_Row_Counter][Local_u8_Column_Counter];
				while(Local_u8_Pin_State==PinLow)
				{
					DIO_VidGetPinValue(KPD_PORT,Local_u8_Kpd_Row_Arr[Local_u8_Row_Counter],&Local_u8_Pin_State);
				}
				DIO_VidSetPinValue(KPD_PORT,Local_u8_Kpd_Column_Arr[Local_u8_Column_Counter],PinHigh);
				return Local_u8_Pressed_Key;
			}
		}//end of 1st loop

		//deactivate current column
		DIO_VidSetPinValue(KPD_PORT,Local_u8_Kpd_Column_Arr[Local_u8_Column_Counter],PinHigh);
	}//end of 2nd loop

	return Local_u8_Pressed_Key;


}//END of function



void KPD_VidInit(void)
{
	/* For Keypad */

	/* pin 0-3 -> output */

	DIO_VidSetPinDirection(KPD_PORT,KPD_COLUMN_0,Output);
	DIO_VidSetPinDirection(KPD_PORT,KPD_COLUMN_1,Output);
	DIO_VidSetPinDirection(KPD_PORT,KPD_COLUMN_2,Output);
	DIO_VidSetPinDirection(KPD_PORT,KPD_COLUMN_3,Output);

	/* set columns high (pull up resistor) */

	DIO_VidSetPinValue(KPD_PORT,KPD_COLUMN_0,PinHigh);
	DIO_VidSetPinValue(KPD_PORT,KPD_COLUMN_1,PinHigh);
	DIO_VidSetPinValue(KPD_PORT,KPD_COLUMN_2,PinHigh);
	DIO_VidSetPinValue(KPD_PORT,KPD_COLUMN_3,PinHigh);

	/* pin 4-7 -> input */

	DIO_VidSetPinDirection(KPD_PORT,KPD_ROW_0,Input);
	DIO_VidSetPinDirection(KPD_PORT,KPD_ROW_1,Input);
	DIO_VidSetPinDirection(KPD_PORT,KPD_ROW_2,Input);
	DIO_VidSetPinDirection(KPD_PORT,KPD_ROW_3,Input);


	/* set rows high (pull up resistor) */

	DIO_VidSetPinValue(KPD_PORT,KPD_ROW_0,PinHigh);
	DIO_VidSetPinValue(KPD_PORT,KPD_ROW_1,PinHigh);
	DIO_VidSetPinValue(KPD_PORT,KPD_ROW_2,PinHigh);
	DIO_VidSetPinValue(KPD_PORT,KPD_ROW_3,PinHigh);



}
