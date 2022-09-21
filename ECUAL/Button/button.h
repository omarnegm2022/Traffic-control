/*
 * button.h
 *In this driver, volatile specialty will show up.
 * Created: 9/4/2022 2:53:24 PM
 *  Author: omarn
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "../../Utilities/types.h"	//for the structure members
// including drivers from lower layer:
#include "../../MCAL/DIO/dio.h"

typedef struct push_button{
	uint8_t button_port;
	uint8_t button_pin;
	uint8_t* button_value;	// as there are 2 configurations of button connection to the port
}button;

typedef enum buttonError
{
	BUTTON_ERROR, BUTTON_OK
}EN_buttonCheck_t;


EN_buttonCheck_t button_init(button* buttons);	
EN_buttonCheck_t button_read(button* buttons);

// button test module
void button_main();

#endif /* BUTTON_H_ */