/*
 * app.h
 *
 * Created: 9/4/2022 11:13:17 PM
 *  Author: omarn
 */ 


#ifndef APP_H_
#define APP_H_

// dio
#include "../MCAL/DIO/dio.h"

//timer
#include "../MCAL/Timer/timer.h"

//interrupt
#include "../MCAL/Interrupt/interrupt.h"

// Input devices:
#include "../ECUAL/button/button.h"

// Output devices:
#include "../ECUAL/LED/LED.h"


void APP_init();
void APP_run();

#endif /* APP_H_ */