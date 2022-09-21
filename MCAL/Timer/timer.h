/*
 * T_registers.h
 *
 * Created: 9/5/2022 10:22:21 PM
 *  Author: omarn
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "../../Utilities/types.h"
#include "../../Utilities/bit_ops.h" //used in manipulating timer related values

typedef unsigned int uint32_t;
// this type used for prescaler and number of overflows

//defining modes:
#define Normal 0x00
/*
#define CTC "clear on compare"
#define f_PWM "fast modulation"
#define PWM_C "correct modulation"
#define CNT "counter"
*/

typedef enum timerError
{
	TIMER_OK,NOT_AVAILABLE_MODE,WRONG_START_VALUE,WRONG_PRESCALER,
	TIMER_NOT_RESET,TIMER_NOT_SET
}EN_timerCheck_t;


//1. set timer configurations
EN_timerCheck_t timer_init(uint8_t mode);
//2. start the timer, according to the required delay
EN_timerCheck_t timer_start(uint32_t prescaler,uint8_t start_value); //extra argument: uint32_t overflows
//3. get timer state, TIFR value
uint8_t timer_state(uint8_t state_flag);
//4. stop the timer
EN_timerCheck_t timer_stop(uint32_t* overflow_counter); // takes that parameter to clear it

// Timer test module
void timer_main();


#endif /* T_REGISTERS_H_ */