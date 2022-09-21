/*
 * timer.c
 * [Documentation]: contains and mode_setter and timer starter and initializer
 * , controlling timer status.
 * Created: 9/8/2022 1:00:31 PM
 *  Author: omarn
 */ 
#include "timer.h"
#include "../../Utilities/register_file.h"	//contains timer registers


//uint32_t overflow_getter = 0;

EN_timerCheck_t timer_init(uint8_t mode)
{	// set timer mode of operation
	if (mode == Normal)	// No need to other modes
	{	TCCR0 = mode;	
		return TIMER_OK;	}
	else	//error handling of mode 
		return NOT_AVAILABLE_MODE;
		
		
}

EN_timerCheck_t timer_start(uint32_t prescaler,uint8_t start_value)
{
	//1. set initial value to start with
	if (start_value >=0 && start_value <=256)
		TCNT0 = start_value;	
	else	// error handling of initial value
		return WRONG_START_VALUE;
	
	//[extra]. set number of overflows according to the delay calculations
	//overflow_getter = overflows;
	// not expecting negative values
	
	//2. clear timer overflow flag before starting
	SET_BIT(TIFR,0);	// method from the data sheet, page:89
	switch(prescaler)
	{//3. set the prescaler of the tick time 
		case 0:
		{
			SET_BIT(TCCR0,0);
			return TIMER_OK;
		}
		case 8:
		{
			SET_BIT(TCCR0,1);
			return TIMER_OK;
		}
		case 64:
		{
			SET_BIT(TCCR0,0);
			SET_BIT(TCCR0,1);
			return TIMER_OK;
		}
		case 256:
		{
			SET_BIT(TCCR0,2);
			return TIMER_OK;
		}
		case 1024:
		{
			SET_BIT(TCCR0,2);
			SET_BIT (TCCR0,0);
			return TIMER_OK;
		}
		default:	//error handling of the start function
			return WRONG_PRESCALER;
	}
	return TIMER_OK;
}

uint8_t timer_state(uint8_t state_flag)
{	if(!TCCR0)
		return 1;	//so the timer isn't set to start, while state_flag is still initialized 0
	/*while ((TIFR&(1<<0)) == 0)
	{
		state_flag = 0;
	}
	
	state_flag = 1;
	*/
	// get timer state
	return state_flag;
}

EN_timerCheck_t timer_stop(uint32_t* overflow_counter)
{	// reset the timer
	TCCR0 = 0x00;
	*overflow_counter = 0;
	if(!TCCR0 && ! *overflow_counter)
		return TIMER_OK;
	return TIMER_NOT_RESET;
}