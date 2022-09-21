/*
 * test.c
 *
 * Created: 9/11/2022 8:43:55 PM
 *  Author: omarn
 */ 
#include "button.h"

button b1 = {'D',3,0x00};
void button_main(){
	button_init(&b1);
	
	button_read(&b1);
}