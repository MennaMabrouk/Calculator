#include "STD_TYPES.h"
#include <util/delay.h>
#include "DIO_interface.h"
#include "LCD_config.h"
#include "LCD_interface.h"


void LCD_VidSendCommand(u8 Copy_u8Command)
{
	// setting RS to 0 -> command
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_RS_PIN ,PinLow);

	//setting RW to 0 -> write (active low)
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_RW_PIN ,PinLow);

	//setting command to data pin
	DIO_VidSetPortValue(LCD_DATA_PORT,Copy_u8Command);

	//sending pulse to enable (Falling Edge)
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN ,PinHigh);
	_delay_ms(2);
	DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN ,PinLow);

}



void LCD_VidSendData(u8 Copy_u8Data)
{
	// setting RS to 1 -> data
		DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_RS_PIN ,PinHigh);

		//setting RW to 0 -> write (active low)
		DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_RW_PIN ,PinLow);

		//setting data to data pin
		DIO_VidSetPortValue(LCD_DATA_PORT,Copy_u8Data);

		//sending pulse to enable (Falling Edge)
		DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN ,PinHigh);
		_delay_ms(2);
		DIO_VidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN ,PinLow);

}

void LCD_VidInit(void)
{
	// wait for 30ms LCD power (from data sheet)
	_delay_ms(40);

	//Function	 set command-> 2 lines, 5*8 Font size (from data sheet)
	LCD_VidSendCommand(0b00111000);
	//Display on off control-> display enable , disable cursor , disable blink cursor (from data sheet)
	LCD_VidSendCommand(0b00001100);
	//Clear Display (from data sheet)
	LCD_VidSendCommand(1);



}

void LCD_VidSendString(u8 * Copy_u8ptrString)
{
	/* NORMAL SendString */
/*
	u8 Local_u8Iterator=0;
	while(Copy_u8ptrString[Local_u8Iterator] !='\0')
	{
		LCD_VidSendData(Copy_u8ptrString[Local_u8Iterator]);
		Local_u8Iterator++;
	}
*/

	/* Modified SendString */

	u8 Local_u8Iterator=0 , CheckSecondLine=0;
	while(Copy_u8ptrString[Local_u8Iterator] !='\0')
	{
		if(Local_u8Iterator<16)
		{

			LCD_VidSendData(Copy_u8ptrString[Local_u8Iterator]);
		}
		else
		{

			LCD_VidSetPosition(1,CheckSecondLine);
			LCD_VidSendData(Copy_u8ptrString[Local_u8Iterator]);
			CheckSecondLine++;
		}
		Local_u8Iterator++;
	}


}



//to set position
void LCD_VidSetPosition(u8 Copy_u8Row , u8 Copy_u8Column)
{
	if(Copy_u8Row==LCD_ROW_1)
	{
		LCD_VidSendCommand((0x80)+(Copy_u8Column));
	}
	else if(Copy_u8Row==LCD_ROW_2)
	{ /*  + -> oring
		  0x80 -> 10000000 set DDRAM address from data sheet
		  0x40 -> 64 in decimal (address beginning of 2nd line)  */

		LCD_VidSendCommand((0x80)+(0x40)+(Copy_u8Column));
	}

}


//to write extra character

// BlockNo in CGRAM , Copy_u8RowPostion,Copy_u8ColumnPostion --> x,y coordinates
void LCD_VidWriteExtraCharacter(u8 *Copy_u8ptrArr,u8 Copy_u8BlockNo,u8 Copy_u8RowPostion,u8 Copy_u8ColumnPostion)
{
	/*  write inside CGRAM
	 	+ -> oring
		0x40 -> 0b01000000 set CGRAM address from data sheet  */
		u8 Local_u8CGRAMAddress=0 , Copy_u8Iterator;
		Local_u8CGRAMAddress= Copy_u8BlockNo*8;  //to move from block to block , each block 1 byte
		LCD_VidSendCommand((0x40)+(Local_u8CGRAMAddress));
		for(Copy_u8Iterator=0;Copy_u8Iterator<8;Copy_u8Iterator++)
		{
			LCD_VidSendData(Copy_u8ptrArr[Copy_u8Iterator]);
		}

		//return to DDRAM to print
		LCD_VidSetPosition(Copy_u8RowPostion,Copy_u8ColumnPostion);
		LCD_VidSendData(Copy_u8BlockNo); //DDRAM sees 0-7 addresses -> understand it's extra character
}



void LCD_VidSendNumber(u16 Copy_u16Number)
{
	u8 Local_u8String[16];
	itoa(Copy_u16Number,Local_u8String,10); // 10 -> base (decimal)
	LCD_VidSendString(Local_u8String);
}
