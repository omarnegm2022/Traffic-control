/*
 * app.c
 *
 * Created: 9/4/2022 11:13:34 PM
 *  Author: omarn
 */ 
#include "app.h"
// Defining traffic colors as integers to be used as indices in LEDs structure arrays
#define GREEN 0
#define YELLOW 1
#define RED 2
// pedestrian_button flag
uint8_t pedestrian_mode = 0;
uint8_t pedestrian_mode_cycle = 0; // used for handling more/longer than one short press on the button
// colors' indexing
uint8_t car_color = 0;
uint8_t pedestrian_color = 2;
// direction of each traffic sequence
int car_sequence = 1;
int pedestrian_sequence = -1;

//1. set the project configurations:
//1-1. 3 LEDs  for cars, 3 LEDs for pedestrian
led car_traffic[]={ {portA,pin0},	//green
		{portA,pin1},	//yellow
	{portA,pin2}};	//red
led pedestrian_traffic[]= { {portB,pin0},	//green
		{portB,pin1},	//yellow
{portB,pin2}};	//red
//1-2. 1 push button: to the INT0 pin
button pedestrian_button = {portD,pin2,0};
	
//1-3. number of overflows for 5-second delay
/*
F_cpu = 1MHz
prescaler = 1024	//for less overflows and approximate integer value for the initial starting
maximum delay for 1 overflow = 262.14 millisecond 
init_val = 11.859, (ceil): 12 
*/
//Defining some timer specs for the 5-sec delay
#define PRESCALER 1024
#define OVERFLOWS 20
#define TIMER_INIT 12
uint32_t overflow_counter = 0;

void allow_pedestrian();	//starts pedestrian mode

void APP_init()
{
	//2. initiate the project drivers
	//2-1. initiate the LEDs
	for (int i = 0; i<3; i+= 1)
	{
		LED_init(car_traffic+i);
		LED_init(pedestrian_traffic+i);
	}	
	//2-2.	initiate the button
	button_init(&pedestrian_button);
	//2-3. initiate the timer
	timer_init(Normal);
	//2-4. initiate the interrupt 
	INT_init(RISE_EDGE,INT0_control);
}
/////////////////////////////////////////////////////////
void APP_run()
{
	//3. start the project
	//3-1. start the timer
	timer_start(PRESCALER,TIMER_INIT);
	//3-2. turn on the next LED of each traffic(starting with GREEN for cars' traffic)
 //////////////////////////cars' traffic////////////////////////////////////
	if(car_color == GREEN || car_color == RED)
	LED_on(&car_traffic[car_color]);
 ///////////////////////////pedestrian traffic///////////////////////////////////
	if(pedestrian_color == GREEN || pedestrian_color == RED)
	LED_on(&pedestrian_traffic[pedestrian_color]);
	
	//3-3. check the timer sate
	uint8_t state_flag = 0;
	
	while(overflow_counter<OVERFLOWS)
	{
		//[timer loop]1. check timer state
		while ((TIFR&(1<<0)) == 0)
		{
			// Start the pedestrian mode when the interrupt occurs
			if(pedestrian_mode)	//interrupt
				allow_pedestrian();
//////////////////////////////////////////////////////////////////////////
			state_flag = 0;
			timer_state(state_flag);
		}
		
		//[timer loop]2. clearing overflow flag
		state_flag = 1;	
		TIFR |= (1<<0);	
		//[timer loop]3. increment the overflow_counter till reaching the target
		overflow_counter++;
//NOTE: YELLOW light is lit after incrementing the overflow_counter to make last state: on
//.. and inside the timer loop to make the LED blink	
	//////////////////////////cars' traffic////////////////////////////////////
		if(car_color == YELLOW && overflow_counter % 4 == 0 )	//second condition to..
		// 	make blinking being able to be seen at each second.
		LED_toggle(&car_traffic[car_color]);
	///////////////////////////pedestrian traffic///////////////////////////////////
		if(pedestrian_color == YELLOW && overflow_counter % 4 == 0 )
		LED_toggle(&pedestrian_traffic[pedestrian_color]);
	}
	timer_state(state_flag);
	
	//3-4. stop the timer at the final overflow of 5 seconds
	timer_stop(&overflow_counter);
	
	//3-5. turn off the current cars' traffic LED
	LED_off(&car_traffic[car_color]);
	//3-5. turn off the current pedestrian's traffic LED
	LED_off(&pedestrian_traffic[pedestrian_color]);
//////////////////////////////////////////////////////////////
	//3-6. change to the next LED of cars' traffic 
	car_color += car_sequence;
	//3-7. change the direction of cars' traffic sequence backward
	if(car_color == RED || car_color == GREEN)
		car_sequence *= -1;
		
	//3-7. change to the next LED of pedestrian's traffic
	pedestrian_color += pedestrian_sequence;
	
	//3-7. change the direction of pedestrian's traffic sequence backward
	if(pedestrian_color == GREEN || pedestrian_color == RED)
		pedestrian_sequence *= -1;
// In case of pedestrian mode:
	if(pedestrian_mode_cycle)
		--pedestrian_mode_cycle;
}
/************************************************************************/
/*               interrupt service routine                              */
/************************************************************************/
ISR(EXT_INT_0)
{	
	if(!pedestrian_mode_cycle)	// user stories 4 and 5
	{	++pedestrian_mode;
		pedestrian_mode_cycle = 3;	}
	/*if (car_color == 2)	//red
		pedestrian_color = 0; //green
	else if(car_color == 0 || car_color == 1)
	pedestrian_color = 2;	//red, then yellow
	*/
	//[to be deleted]: remember, small function.
}
//////////////////////////////////////////////////////////////////////////
void allow_pedestrian(void)
{	
// user story 1
	 if (car_color < pedestrian_color)
		// Before changing to yellow, turn off both LEDs
		{	LED_off(&car_traffic[car_color]);
		LED_off(&pedestrian_traffic[pedestrian_color]);
		car_color += 1;
		pedestrian_color -= 1;
		// Reset the timer
		TCCR0 = 0x00;
		overflow_counter = 0;
				TIFR |= (1<<0);	
		TCNT0 = TIMER_INIT;
		TCCR0 |= (1<<2) | (1<<0);	}
		
// user story 2	
	else if (car_color == pedestrian_color)
	// Reset the timer
	{	TCCR0 = 0x00;
		overflow_counter = 0;
	TCNT0 = TIMER_INIT;
		TIFR |= (1<<0);	
	TCCR0 |= (1<<2) | (1<<0);
	car_sequence = 1;
	pedestrian_sequence = -1;	}
	
// user story 3	
	else if (car_color > pedestrian_color)
	// Reset the timer
	{	TCCR0 = 0x00;
		overflow_counter = 0;
	TCNT0 = TIMER_INIT;
		TIFR |= (1<<0);	
	TCCR0 |= (1<<2) | (1<<0);	}

// Finally, return to normal mode
	pedestrian_mode = 0;	
}