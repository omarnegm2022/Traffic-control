/*
 * test.c
 *
 * Created: 9/11/2022 8:22:42 PM
 *  Author: omarn
 */ 


#include "LED.h"

led l1 = {'B',5};
void LED_main(){
	
	LED_init(&l1);
	
	LED_on(&l1);
	LED_off(&l1);
	
	LED_toggle(&l1);
	LED_blink(&l1);
}