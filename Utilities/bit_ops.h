/*
 * bit_ops.h
 *
 * Created: 9/4/2022 9:22:03 PM
 *  Author: omarn
 */ 


#ifndef BIT_OPS_H_
#define BIT_OPS_H_

// defining functions of bitwise operations, like macros// where: x: port_letter, n: pin_number
#define SET_BIT(x,n)  x|= (1<<n)
#define CLR_BIT(x,n)  x&= ~(1<<n)
#define	RD_BIT(x,n)  ((x&(1<<n))>>n)
#define TGL_BIT(x,n)  x^= (1<<n)




#endif /* BIT_OPS_H_ */