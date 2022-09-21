/*
 * test.c
 *
 * Created: 9/9/2022 1:01:32 AM
 *  Author: omarn
 */ 
#include "dio.h"

void DIO_main()
{
	uint8_t port_letter = portB,  pin_number = 0,  direction = 5,value = 1;
	 DIO_init( port_letter,  pin_number,  direction);
	 
	//write the value of PORT pin
	 DIO_write( port_letter,  pin_number,  value);
	//toggle the value of PORT pin
	
	 DIO_toggle( port_letter,  pin_number);
	//read the value of PIN pin
	 DIO_read( port_letter,  pin_number, &value);

	
}