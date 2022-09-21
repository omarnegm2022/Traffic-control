/*
 * LED.h
 *
 * Created: 9/4/2022 1:52:39 PM
 *  Author: omarn
 */ 


#ifndef LED_H_
#define LED_H_

#include "../../Utilities/types.h"	//for the structure members
// including drivers from lower layer:
#include "../../MCAL/DIO/dio.h"

typedef struct LED{
	uint8_t led_port;
	uint8_t led_pin;
	}led;
	
typedef enum ledError
{
	LED_ERROR,LED_OK,LED_ON,LED_OFF,pin_USED
}EN_ledCheck_t;

EN_ledCheck_t LED_init(led* lamps);	
EN_ledCheck_t LED_on(led* lamps);
EN_ledCheck_t LED_off(led* lamps);
EN_ledCheck_t LED_toggle(led* lamps);
EN_ledCheck_t LED_blink(led* lamps);

// LED test module
void LED_main();
#endif /* LED_H_ */