/*
 * interrupt.c
 * [Documentation]: contains interrupt registers and flags, and interrupt_number
 * Created: 9/8/2022 12:59:37 PM
 *  Author: omarn
 */ 

#include "interrupt.h"
#include "../../Utilities/bit_ops.h"

EN_interruptCheck_t INT_init(uint8_t type, uint8_t control)

{
	//1. enable the global interrupt(I-bit of SREG)
	sei();
	//handling error
	if (RD_BIT(SREG,7) == 0)
		return INTERRUPT_ERROR;
	//2. choose the interrupt sensor of INT0, as well as the interrupt type
	if(type>=0 && type<=2)
		SET_BIT(MCUCR,type);
	else if(type == 3)
	{
		SET_BIT(MCUCR,1);
		SET_BIT(MCUCR,0);
	}
	else	//handling error
		return WRONG_TYPE;
	//3. enable the external interrupt, of INT0 bit in GICR
	if(control !=6)		//handling error
		return WRONG_ENABLE;
	SET_BIT(GICR,6);
	
	return INTERRUPT_OK;
}