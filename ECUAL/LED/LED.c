/*
 * LED.c
 * [Documentation]: contains LEDs functionalities as well as initializing connected pins.
 * this driver is for output device
 * Created: 9/4/2022 1:52:26 PM
 *  Author: omarn
 */ 
#include "LED.h"
//flags used in error handling:
EN_ledCheck_t LED_init_state = LED_OK;
EN_ledCheck_t LED_on_state = LED_ON;
EN_ledCheck_t LED_off_state = LED_OFF;

uint8_t* test_address = 0x00;

//1.set the connected pin direction to: output
EN_ledCheck_t LED_init(led* lamps)
{
	/*	DIO_read(lamps->led_port,lamps->led_pin,test_address);
	if(*test_address)//i.e. there is another LED had been connected to this pin
		return pin_USED;
	//NOTE: this could be done by reading DDR of the pin	*/
	
	if (DIO_init(lamps->led_port,lamps->led_pin,OUTPUT) == DIO_OK)
		{
			LED_init_state = LED_OK;
			return LED_OK;
		}
	LED_init_state = LED_ERROR;		
	return LED_ERROR;	
}
//2. use the led
EN_ledCheck_t LED_on(led* lamps)
{//put HIGH value on the PORT pin
	DIO_read(lamps->led_port,lamps->led_pin,test_address);	//NOTE: takes 46 cycles(46 microseconds)
	if (! *test_address)	//NOTE: THIS LINE takes 8 cycles(8 microseconds)
//NOTE: same time for each of those lines to their corresponding in LED_off(), so..
// No matter if commented test of LED_on or LED_off, in order to take less time even we wrote the
//.. same value to the LED pin.	
	{	DIO_write(lamps->led_port,lamps->led_pin,HIGH);
		LED_on_state = LED_ON;
		return LED_ON;	}
	LED_on_state = LED_ERROR;	
	return	LED_ERROR;
}

EN_ledCheck_t LED_off(led* lamps)
{//clear PORT value of the connected pin
	DIO_read(lamps->led_port,lamps->led_pin,test_address);	
	if (*test_address)	
	{	DIO_write(lamps->led_port,lamps->led_pin,LOW);
		LED_off_state = LED_OK;
		return LED_OFF;	}
	LED_off_state = LED_ERROR;
	return	LED_ERROR;
	
}

EN_ledCheck_t LED_toggle(led* lamps)
{//change the PORT value of the connected pin
	if (LED_init_state == LED_OK)
		{	DIO_toggle(lamps->led_port,lamps->led_pin);
		return LED_OK;	}
	return LED_ERROR;
}

EN_ledCheck_t LED_blink(led* lamps)	//NOTE: it needs timer loop inside it to make blinking visible
{// quick change between off and on
	//while(1)	// won't do good
	
	if(LED_off(lamps) && LED_on(lamps))	//LED_ON > 0
		return LED_OK;
	if(LED_on(lamps) && LED_off(lamps))	//LED_OFF > 0
		return LED_OK;
	return LED_ERROR;
}