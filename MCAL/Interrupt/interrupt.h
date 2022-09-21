/*
 * I_registers.h
 * 
 * Created: 9/8/2022 1:00:54 PM
 *  Author: omarn
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "../../Utilities/types.h"
#include "../../Utilities/register_file.h"	//contains interrupt registers
typedef enum interruptError
{
	INTERRUPT_OK,WRONG_PORT,WRONG_PIN,NOT_AVAILABLE_SOURCE,WRONG_SENSOR,
	WRONG_TYPE,INTERRUPT_ERROR,ROUTINE_STUCK,WRONG_ENABLE
}EN_interruptCheck_t;

// external_interrupt source
#define INT0_port PORTD
#define INT0_pin 2
#define INT0_control 6
// interrupt types definitions for the used source
#define LOW_LEVEL 0
#define ANY_LOGIC 1	//i.e. falling or rising edge
#define FALL_EDGE 2
#define RISE_EDGE 3	// will have special bitwise operation
/************************************************************************/
/*                        external_interrupt vectors                    */
/************************************************************************/
//request0
#define EXT_INT_0 __vector_1
//request1
#define EXT_INT_1 __vector_2
//request2
#define EXT_INT_2 __vector_3
/************************************************************************/
/*                        external_interrupt functions                  */
/************************************************************************/
//macro of the interrupt service routine
#define ISR(INT_VECT) void INT_VECT(void) __attribute__((signal,used));\
void INT_VECT(void)
// enable the global interrupt in SREG
# define sei()  __asm__ __volatile__ ("sei" ::: "memory")
// clear I-bit in SREG
# define cli()  __asm__ __volatile__ ("cli" ::: "memory")

EN_interruptCheck_t INT_init(uint8_t type, uint8_t control);/*description is inside the definition*/
//Interrupt test module:
void INT_main();

#endif /* I_REGISTERS_H_ */

