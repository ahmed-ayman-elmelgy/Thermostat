/*
 * Motor.h
 *
 * Created: 1/17/2022 10:24:14 AM
 *  Author: Ahmed_Ayman
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include "avr/io.h"
#include <stdint.h>
#include "HAL_GPIO.h"
#include "Utilites.h"

#define Total_MOTORS	2

#define MOTOR_1			0u
#define MOTOR_2			1u

typedef struct
{
	StrGPIO_t        Port[2] ;
	uint8_t          Pin[2]  ;
}Motor_Pins;

typedef struct
{
	Motor_Pins Motor[Total_MOTORS];
	
}MotorSelect_t ;



typedef enum { MOTOR_OK , MOTOR_PARAM_ERROR , MOTOR_CONFIG_ERROR , MOTOR_PWM_ERROR  }MOTOR_STATUS_t;


typedef enum {DIR_LEFT , DIR_RIGHT , DIR_FORWARD , DIR_BACKWARD , DID_STOP }Motor_DIR_t;
	
	
	
MOTOR_STATUS_t Motor_Init(void);


MOTOR_STATUS_t Motor_Dir(Motor_DIR_t DIR , uint8_t Speed );




#endif /* MOTOR_H_ */