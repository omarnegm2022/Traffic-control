/*
 * test.c
 *
 * Created: 9/9/2022 10:31:59 PM
 *  Author: omarn
 */ 
#include "timer.h"
#define CTC 'T'
void timer_main()
{
	uint32_t prescaler = 0;
	uint32_t start_value = 300;
	uint32_t overflow_counter = 100;
	uint8_t mode = CTC ;
	uint8_t state_flag = 0;	// as the timer loop is outside the driver
	//1. set timer configurations
	 timer_init( mode);
	//2. start the timer, according to the required delay
	 timer_start( prescaler, start_value);
	//3. get timer state, TIFR value
	 timer_state( state_flag);	//expected to return: 1
	//4. stop the timer
	 timer_stop( &overflow_counter);

}