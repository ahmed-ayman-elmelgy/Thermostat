/*
 * Library.h
 *
 * Created: 1/12/2022 2:18:22 PM
 *  Author: Ali Hassan Dorgham
 */ 


#ifndef LIBRARY_H_
#define LIBRARY_H_

#ifndef  F_CPU 

//#warning "You use F_CPU = 8 MHZ"
#define F_CPU 8000000UL

#endif

/* AVR */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/* Standard Libraries */
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
#include "math.h"
#include "stdint.h"

#endif /* LIBRARY_H_ */
