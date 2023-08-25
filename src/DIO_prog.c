#include "BIT_Math.h"
#include "STD_TYPES.h"
#include "DIO_private.h"
#include "DIO_interface.h"

void DIO_VidSetPinDirection(u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Direction)
{

if(Copy_u8Direction==Input)
{
	switch(Copy_u8Port)
	{
	case Port_A:   clear_bit(DDRA , Copy_u8Pin);
				       break;
	case Port_B:   clear_bit(DDRB , Copy_u8Pin);
					   break;
	case Port_C:   clear_bit(DDRC , Copy_u8Pin);
					   break;
	case Port_D:   clear_bit(DDRD , Copy_u8Pin);
					   break;
	}
}
else if(Copy_u8Direction==Output)
{
	switch(Copy_u8Port)
		{
		case Port_A:   set_bit(DDRA , Copy_u8Pin);
					       break;
		case Port_B:   set_bit(DDRB , Copy_u8Pin);
						   break;
		case Port_C:   set_bit(DDRC , Copy_u8Pin);
						   break;
		case Port_D:   set_bit(DDRD , Copy_u8Pin);
						   break;
		}
}

}

void DIO_VidSetPinValue(u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Value)
{
	if(Copy_u8Value==PinLow)
	{
		switch(Copy_u8Port)
		{
		case Port_A:   clear_bit(PORTA , Copy_u8Pin);
						   break;
		case Port_B:   clear_bit(PORTB , Copy_u8Pin);
						   break;
		case Port_C:   clear_bit(PORTC , Copy_u8Pin);
						   break;
		case Port_D:   clear_bit(PORTD , Copy_u8Pin);
						   break;
		}
	}
	else if(Copy_u8Value==PinHigh)
	{
		switch(Copy_u8Port)
			{
			case Port_A:   set_bit(PORTA , Copy_u8Pin);
						       break;
			case Port_B:   set_bit(PORTB , Copy_u8Pin);
							   break;
			case Port_C:   set_bit(PORTC , Copy_u8Pin);
							   break;
			case Port_D:   set_bit(PORTD , Copy_u8Pin);
							   break;
			}

	}

}

void DIO_VidGetPinValue(u8 Copy_u8Port , u8 Copy_u8Pin , u8 *pu8Data)
{
	switch(Copy_u8Port)
				{
				case Port_A:   *pu8Data = get_bit(PINA , Copy_u8Pin);
							   break;
				case Port_B:   *pu8Data = get_bit(PINB , Copy_u8Pin);
								   break;
				case Port_C:   *pu8Data = get_bit(PINC , Copy_u8Pin);
								   break;
				case Port_D:   *pu8Data = get_bit(PIND , Copy_u8Pin);
								   break;
				}

}


void DIO_VidSetPortDirection(u8 Copy_u8Port ,  u8 Copy_u8Direction)
{

	if(Copy_u8Direction==Input)
	{
		switch(Copy_u8Port)
		{
		case Port_A:   DDRA = 0x00;
					       break;
		case Port_B:   DDRB = 0x00;
						   break;
		case Port_C:   DDRC = 0x00;
						   break;
		case Port_D:   DDRD = 0x00;
						   break;
		}
	}
	else if(Copy_u8Direction==Output)
	{
		switch(Copy_u8Port)
			{
			case Port_A:   DDRA = 0xFF;
						       break;
			case Port_B:   DDRB = 0xFF;
							   break;
			case Port_C:   DDRC = 0xFF;
							   break;
			case Port_D:   DDRD = 0xFF;
							   break;
			}
	}
}

void DIO_VidSetPortValue(u8 Copy_u8Port, u8 Copy_u8Value)
{

			switch(Copy_u8Port)
			{
			case Port_A:   PORTA = Copy_u8Value;
							   break;
			case Port_B:   PORTB = Copy_u8Value;
							   break;
			case Port_C:   PORTC = Copy_u8Value;
							   break;
			case Port_D:   PORTD = Copy_u8Value;
							   break;
			}



}



void DIO_VidGetPortValue(u8 Copy_u8Port  , u8 *pu8Data)
{
	switch(Copy_u8Port)
					{
					case Port_A:   *pu8Data = PINA;
								   break;
					case Port_B:   *pu8Data = PINB;
									   break;
					case Port_C:   *pu8Data = PINC;
									   break;
					case Port_D:   *pu8Data = PIND;
									   break;
					}
}
