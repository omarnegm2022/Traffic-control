/*
 * dio.h
 *
 * Created: 9/4/2022 8:48:56 PM
 *  Author: omarn
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "../../Utilities/types.h"
// defining parameters values of:
//port_letter:-
#define portA 'A'
#define portB 'B'
#define portC 'C'
#define portD 'D'
//pin_number:-		//  [9/4/2022 omarn]
#define pin0 0
#define pin1 1
#define pin2 2
#define pin3 3
#define pin4 4
#define pin5 5
#define pin6 6
#define pin7 7

//directions:-
#define INPUT 0
#define  OUTPUT 1
//values:-
#define HIGH 1
#define LOW 0

typedef enum dioError
{
	DIO_OK,WRONG_LETTER,WRONG_NUMBER,WRONG_VALUE,WRONG_DIRECTION
}EN_dioCheck_t;


//initialize dio directions
EN_dioCheck_t DIO_init(uint8_t port_letter, uint8_t pin_number, uint8_t direction);
//write the value of PORT pin
EN_dioCheck_t DIO_write(uint8_t port_letter, uint8_t pin_number, uint8_t value);	
//toggle the value of PORT pin
EN_dioCheck_t DIO_toggle(uint8_t port_letter, uint8_t pin_number);	
//read the value of PIN pin			
EN_dioCheck_t DIO_read(uint8_t port_letter, uint8_t pin_number, uint8_t* value);

//NOTE: for such functions -like read- its direct return is used for error handling, so make other things..
//.. you want to have from these functions to return as pointers.

// DIO test module
void DIO_main();
#endif /* DIO_H_ */