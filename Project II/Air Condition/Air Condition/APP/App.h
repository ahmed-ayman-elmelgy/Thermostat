/*
 * App.h
 *
 * Created: 1/17/2022 8:33:46 PM
 *  Author: Ahmed_Ayman
 */ 


#ifndef APP_H_
#define APP_H_

#include "ADC.h"
#include "keypad.h"
#include "DIO.h"
#include "Motor.h"
#include "lcd.h"
#include <avr/interrupt.h>
#include "Library.h"


typedef struct
{
	uint8_t Current_Temp ;
	uint8_t Low_Temp ;		/* low temp that the motor can stop */
	uint8_t Previous_Temp ;
	/* high temp we can determine how to config it through our Discussion */
	uint8_t Current_Speed ;
	uint8_t Previous_Speed ;
	/*	if we need to control Direction we can use variable to hold current direction */
}App_Handler_t;


void App_Init(void);



void App_Update(void);


#endif /* APP_H_ */