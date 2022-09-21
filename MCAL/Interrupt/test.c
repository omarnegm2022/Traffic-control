/*
 * test.c
 *
 * Created: 9/9/2022 10:19:13 PM
 *  Author: omarn
 */ 
#include "interrupt.h"
 void INT_main()
 {uint8_t type = RISE_EDGE, control = INT0_control ;
	 
		INT_init(type,control);
 }