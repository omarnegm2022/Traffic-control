/*
 * button.c
 * [Documentation]: contains button functionalities as well as initializing connected pin.
 * this driver is for output device
 * Created: 9/4/2022 2:52:54 PM
 *  Author: omarn
 */ 
#include "button.h"

//flags used in error handling:
EN_buttonCheck_t button_init_state = BUTTON_OK;

//1. set the connected pin direction to: input
EN_buttonCheck_t button_init(button* buttons)//(uint8_t button_prot, uint8_t button_pin)
{
	if (DIO_init(buttons->button_port,buttons->button_pin,INPUT) == DIO_OK)
		{	button_init_state = BUTTON_OK;
		return BUTTON_OK;	}
	button_init_state = BUTTON_ERROR;	
	return BUTTON_ERROR;
}
//2. get button state
EN_buttonCheck_t button_read(button* buttons)//(uint8_t button_prot, uint8_t button_pin, uint8_t* button_value)
{
	if(button_init_state)	// BUTTON_OK > 0
	{	DIO_read(buttons->button_port,buttons->button_pin,buttons->button_value);
		return BUTTON_OK;	}
	return BUTTON_ERROR;
}