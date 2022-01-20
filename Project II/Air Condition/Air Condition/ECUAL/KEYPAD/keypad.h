 /******************************************************************************
 *
 * [MODULE]: KEYPAD
 *
 * [FILE NAME]: keypad.h
 *
 * [DESCRIPTION]: Header file for the Keypad driver
 *
 * [AUTHOR]: Ahmed Hassan
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "Global_Enums.h"
#include "Bit_Math.h"
#include "Library.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define N_col 3
#define N_row 5

/* Keypad Port Configurations */
#define KEYPAD_PORT_OUT PORTC
#define KEYPAD_PORT_IN  PINC
#define KEYPAD_PORT_DIR DDRC

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* 
 * Description: Function responsible for getting the pressed keypad key 
 */
uint8_t KeyPad_getPressedKey(void);

#endif /* KEYPAD_H_ */
