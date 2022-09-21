/*
 * dio.c
 * [Documentation]: controls general purpose registers of the micro controller 
 * Created: 9/4/2022 8:48:45 PM
 *  Author: omarn
 */ 
#include "dio.h"
#include "../../Utilities/register_file.h"
#include "../../Utilities/bit_ops.h"


//III-1:
EN_dioCheck_t DIO_init(uint8_t port_letter, uint8_t pin_number, uint8_t direction)
{
// 1. test pin_number
	if(pin_number >= 0 && pin_number < 8)
//2. test direction
		if (direction==1 || direction==0){
//3. test port_letter
	switch(port_letter)
	{//4. set the direction of the chosen port to the provided pin_number
		case portA:
			{	if (direction == INPUT)	
					{ CLR_BIT(DDRA,pin_number);	}
				else if (direction == OUTPUT)
					{ SET_BIT(DDRA,pin_number);	}
				return DIO_OK;	}
//////////////////////////////////////////////////////////////////////////
		case portB:
			{	if (direction == INPUT)
					{	CLR_BIT(DDRB,pin_number);	}
				else if (direction == OUTPUT)
					{	SET_BIT(DDRB,pin_number);	}
				return DIO_OK;	}
//////////////////////////////////////////////////////////////////////////
		case portC:
			{	if (direction == INPUT)
					{ CLR_BIT(DDRC,pin_number);	}
				else if (direction == OUTPUT)
					{ SET_BIT(DDRC,pin_number);	}
				return DIO_OK;	}
//////////////////////////////////////////////////////////////////////////
		case portD:
			{	if (direction == INPUT)
					{	CLR_BIT(DDRD,pin_number);	}
				else if (direction == OUTPUT)
					{	SET_BIT(DDRD,pin_number);	}
				return DIO_OK;	}	
//6. error handling in either argument value/////////////////////////
		default:
			{	return WRONG_LETTER;	}
	}
					}
			else 
				return WRONG_DIRECTION;
		else		
			return WRONG_NUMBER;
/************************************************************************/
/*					end of the function                                 */
/************************************************************************/
}

//III-2:
EN_dioCheck_t DIO_write(uint8_t port_letter, uint8_t pin_number, uint8_t value)
{
	// 1. test pin_number
	if(pin_number >=0 && pin_number < 8)
	//2. test value
		if (value==1 || value==0){
		//3. test port_letter
	switch(port_letter)
	{//4. set the PORT value of the chosen port to the provided pin_number
		case portA:
			{	if (value == LOW)
					{	CLR_BIT(PORTA,pin_number);	}
				else if (value == HIGH)
					{	SET_BIT(PORTA,pin_number);	}
				return DIO_OK;	}
//////////////////////////////////////////////////////////////////////////
		case portB:
			{	if (value == LOW)
				{	CLR_BIT(PORTB,pin_number);	}
				else if (value == HIGH)
				{	SET_BIT(PORTB,pin_number);	}
				return DIO_OK;	}
//////////////////////////////////////////////////////////////////////////
		case portC:
			{	if (value == LOW)
					{	CLR_BIT(PORTC,pin_number);	}
				else if (value == HIGH)
					{	SET_BIT(PORTC,pin_number);	}
				return DIO_OK;	}
//////////////////////////////////////////////////////////////////////////
		case portD:
			{	if (value == LOW)
					{	CLR_BIT(PORTD,pin_number);	}
				else if (value == HIGH)
					{	SET_BIT(PORTD,pin_number);	}
				return DIO_OK;	}
//6. error handling in either argument value/////////////////////////
		default:
			{	return WRONG_LETTER;	}
			}
		}
			else
				return WRONG_VALUE;
		else
			return WRONG_NUMBER;
/************************************************************************/
/*					end of the function                                 */
/************************************************************************/
}

EN_dioCheck_t DIO_read(uint8_t port_letter, uint8_t pin_number, uint8_t* value)
{
//1. test pin_number
	if(pin_number >= 0 && pin_number < 8){	
//2. test port_letter
	switch(port_letter)
	{//4. read PIN value of the chosen pin in the chosen port
		case portA:
			{	*value = RD_BIT(PINA,pin_number);
				return DIO_OK;	}
//////////////////////////////////////////////////////////////////////////
		case portB:
			{	*value = RD_BIT(PINB,pin_number);
				return DIO_OK;	}
//////////////////////////////////////////////////////////////////////////
		case portC:
			{	*value = RD_BIT(PINC,pin_number);
				return DIO_OK;	}
//////////////////////////////////////////////////////////////////////////
		case portD:
			{	*value = RD_BIT(PIND,pin_number);
				return DIO_OK;	}
//5. error handling in either argument value/////////////////////////
		default:
			{	return WRONG_LETTER;	}
			}
		}
	else
		return WRONG_NUMBER;
/************************************************************************/
/*					end of the function                                 */
/************************************************************************/
}


EN_dioCheck_t DIO_toggle(uint8_t port_letter, uint8_t pin_number)
{
	//1. test pin_number
	if(pin_number >= 0 && pin_number < 8){
//2. test port_letter
	switch(port_letter)
	{//3. inverse the PORT value of the chosen pin in the chosen port
		case portA:
		{	TGL_BIT(PORTA,pin_number);
		return DIO_OK;	}
		//////////////////////////////////////////////////////////////////////////
		case portB:
		{	TGL_BIT(PORTB,pin_number);
		return DIO_OK;	}
		//////////////////////////////////////////////////////////////////////////
		case portC:
		{	TGL_BIT(PORTC,pin_number);
		return DIO_OK;	}
		//////////////////////////////////////////////////////////////////////////
		case portD:
		{	TGL_BIT(PORTD,pin_number);
		return DIO_OK;	}
//4. error handling in either argument value/////////////////////////
		default:
			{	return WRONG_LETTER;	}
				}
	}
	else
		return WRONG_NUMBER;
/************************************************************************/
/*					end of the function                                 */
/************************************************************************/	
}