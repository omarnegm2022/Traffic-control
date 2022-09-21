/*
 * registers.h
 * is the general purpose register file, where all 32 registers are defined
 * Created: 9/3/2022 10:29:16 PM
 *  Author: omarn
 */ 

#ifndef REGISTER_FILE_H_
#define REGISTER_FILE_H_

#include "../Utilities/types.h"

# define SREG *((volatile uint8_t*)0x5F)

/************************************************************************/
/*                           DIO registers                              */
/************************************************************************/
//portA
# define PORTA *((volatile uint8_t*)0x3B)
# define DDRA *((volatile uint8_t*)0x3A)
# define PINA *((volatile uint8_t*)0x39)

//portB
# define PORTB *((volatile uint8_t*)0x38)
# define DDRB *((volatile uint8_t*)0x37)
# define PINB *((volatile uint8_t*)0x36)

//portC
# define PORTC *((volatile uint8_t*)0x35)
# define DDRC *((volatile uint8_t*)0x34)
# define PINC *((volatile uint8_t*)0x33)

//portD
# define PORTD *((volatile uint8_t*)0x32)
# define DDRD *((volatile uint8_t*)0x31)
# define PIND *((volatile uint8_t*)0x30)

//NOTE: volatile qualifier is used also so that the compiler can't do any optimization on that variable.

/************************************************************************/
/*                          timer registers                             */
/************************************************************************/
# define TIFR *((volatile uint8_t*)0x58)
# define TCCR0 *((volatile uint8_t*)0x53)
# define TCNT0 *((volatile uint8_t*)0x52)
/************************************************************************/
/*                    external_interrupt registers                      */
/************************************************************************/
# define GICR *((volatile uint8_t*)0x5B)
# define MCUCR *((volatile uint8_t*)0x55)
# define MCUCSR *((volatile uint8_t*)0x54)
# define GIFR *((volatile uint8_t*)0x5A)
#endif /* REGISTERS_H_ */