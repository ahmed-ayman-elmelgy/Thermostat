/*
 * Utilites.h
 *
 * Created: 1/6/2022 6:28:34 PM
 *  Author: Ahmed_Ayman
 */ 


#ifndef UTILITES_H_
#define UTILITES_H_




#define  F_CPU			16000000u
#include <avr/io.h>
#include <stdbool.h>
#include "TIMER_Interface.h"
#include "HAL_GPIO.h"

#define  PRIVATE static

typedef enum{Delay_Periodic , Delay_Once }DalayType_t;


typedef enum { UTIL_OK =0 , UTIL_PARAM_ERROR , UTIL_TIM_ERROR } Utilies_Status_t ;

typedef struct {
	TIMCaLL_BackFun Delaycallbackfunction ;
	uint16_t		MsDelay ;
	DalayType_t DelayAttr ;
	
	}DelayConfig_t;


/* 
 * brief : this function used to generate delay in Ms blocking mode 
 * parameter : Instance TIM0 or TIM1 
 * parameter : UsDelay Delay in Us 
 * return : Status  
*/
Utilies_Status_t Utilites_DelayMs_IT(TIMInit_t *  Tim_Handler ,uint16_t MsDelay , DalayType_t Dalay_type , TIMCaLL_BackFun callbackfunction);



/* 
 * brief : this function used to generate delay in Us blocking mode 
 * parameter : Instance TIM0 or TIM1 or TIM1
 * parameter : UsDelay Delay in Us 
 * return : Status 
*/
Utilies_Status_t Utilites_DelayUs(uint8_t TimerInstance  ,  uint16_t UsDelay);



/* 
 * brief : this function used to initialize Software PWM depend on one of Timers TIM0/TIM1 / TIM2 
 * parameter (input): PORT GPIO of required channel must be on of GPIO_
 * parameter (input): PIN_Numv channel number must be one of PIN_ 
 * param (input): Tim_PWM_Handler pointer to selected timer configuration 
 * return : Utilies_Status_t status 
*/
Utilies_Status_t Software_PWM_Init( StrGPIO_t PORT , uint8_t PIN_Num ,TIMInit_t * Tim_PWM_Handler );






/* 
 * brief : this function used to start timer with given configuration (prescaller)
 * param (input): TIMConfig pointer to selected timer configuration that contain Prescaller 
 * return : Utilies_Status_t status 
*/
Utilies_Status_t Software_PWM_Start (TIMInit_t * TIMConfig );





/* 
 * brief : this function used to start timer with given configuration (prescaller)
 * param (input): Tim_PWM_Handler pointer to selected timer configuration that contain Prescaller 
 * param (input): SetDuty desired Duty cycle From (0 t0 100 )
 * return : Utilies_Status_t status 
*/
Utilies_Status_t Software_PWM_UpdateDuty( uint8_t SetDuty  ,TIMInit_t * Tim_PWM_Handler );




/* 
 * brief : this function used to Stop PWM Operation 
 * param (input): Tim_PWM_Handler pointer to selected timer configuration that contain Prescaller 
 * param (input): SetDuty desired Duty cycle From (0 t0 100 )
 * return : Utilies_Status_t status 
*/
Utilies_Status_t Software_PWM_Stop( TIMInit_t * Tim_PWM_Handler );


#endif /* UTILITES_H_ */