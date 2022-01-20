/*
 * TIM_Interface.h
 *
 * Created: 1/10/2022 4:48:32 PM
 *  Author: Ahmed_Ayman
 */ 


#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <stdint.h>




#define  NULL ((void*)0) 



typedef void (*TIMCaLL_BackFun)(void);  /* typedef for function pointer */



#define  PRIVATE   static 



typedef enum { TIM_OK = 0 , TIM_PARAM_ERROR , TIM_CONFIG_ERROR } TIM_Status_t ;



typedef enum {TIM0 = 0  , TIM1 , TIM2 }TIM_Instance_t;
	
	

typedef enum {	TIM_1_Prescaler_0 ,TIM_1_Prescaler_1   , TIM_1_Prescaler_8 ,
				TIM_1_Prescaler_64,TIM_1_Prescaler_256 ,TIM_1_Prescaler_1024 ,
				TIM_1_External_Failing , TIM_1_External_Rising }TIM1_Prescaller_t;

typedef enum {	TIM_0_Prescaler_0 ,TIM_0_Prescaler_1	, TIM_0_Prescaler_8	,
				TIM_0_Prescaler_64,TIM_0_Prescaler_256,TIM_0_Prescaler_1024,
				TIM_0_External_Failing,TIM_0_External_Rising}TIM0_Prescaller_t;
				
typedef enum {	TIM_2_Prescaler_0 ,TIM_2_Prescaler_1 ,TIM_2_Prescaler_8	,								
				TIM_2_Prescaler_32 ,TIM_2_Prescaler_64 ,TIM_2_Prescaler_128	,								
				TIM_2_Prescaler_256	, TIM_2_Prescaler_1024}	TIM2_Prescaller_t;						

	 			
				


#define TIM_PRESCALLER_MASK												0x07u



#define  COMP_A_														0x06u
#define  COMP_B_														0x04u
#define  COMP_A_B_														0xffu



/* define operation modes in timer0 | timer1 TCCR0/2 Mask  0x48 */
#define		TIM8Bit_MODE_MASK											0x48u


#define		TIM_MODE_NORMAL												0x00u 
#define		TIM_MODE_COMP_PWM_PHASE										0x402fffu
#define		TIM_MODE_CTC												0x080fffu
#define		TIM_MODE_COMP_PWM_FAST										0x481fffu

#define     TIM_Mode_InputCapture										0x0000000u
#define		TIM16Bit_InputCapture_CAPTURE_EDGE_MASK						0x0000040u
#define		TIM16Bit_InputCapture_CAPTURE_EDGE_Falling					0x0000000u
#define		TIM16Bit_InputCapture_CAPTURE_EDGE_Rising					0x0000040u



/* Top OCR1x */
/* top is depend on the number of bits */
#define		TIM_MODE_16Bit_MODE_COMP_PWM_FAST_10B						0x13ffu
#define		TIM_MODE_16Bit_MODE_COMP_PWM_FAST_9B						0x11ffu
#define		TIM_MODE_16Bit_MODE_COMP_PWM_FAST_8B						0x10ffu
/* Top OCR1x */
#define		TIM16Bit_MODE_COMP_PWM_FAST_MODE							0x1fffu

	

/* compare output mode with mask 0x30 */
#define		TIM8Bit_COMP_OUT_MASK		 								0x30u
 
#define		TIM_COMP_PIN_OUT_Normal						   				0x00u
#define		TIM_COMP_PIN_OUT_OC_CLR			    						0x20u
#define		TIM_COMP_PIN_OUT_OC_SET										0x30u
#define		TIM_COMP_OUT_NONPWMONLY_PIN_TOG						 		0x10u
	



typedef enum{ 
		TIM_IT_DIS , TIM_0_IT_OVER =0x01	, TIM_0_IT_COMP   =0x02	 ,TIM_1_IT_OVER =0x04,											
		TIM_1_IT_COMPB=0x08	, TIM_1_IT_COMPA  =0x10 ,TIM_1_IT_CAPT  =0x20	,										
		TIM_2_IT_OVER =0x40 	,TIM_2_IT_COMP =0x80 										
}IT_SelBIT_t ; 




	
	#define		_TIM_IT_EN(INT)								   			TIMSK |= ((IT_SelBIT_t)INT)
	#define		TIM_0_IT_MASK									 		0x03u
	#define		TIM_2_IT_MASK								     		0xc0u
	#define		TIM_1_IT_MASK								    		0x3cu



typedef	union {
			struct  
			{
				uint8_t CompAction ;	/* must be one of TIM_COMP_OUT_*/
				uint8_t CompValue  ;	/* value from 0 to 65535 */
				uint8_t CompNum    ;	/* must be one of COMP_(A/B/Both) */		
			}TIM16Bit;
			struct {
				
				uint8_t CompAction ;	/* must be one of TIM_COMP_OUT_*/
				uint8_t CompValue  ;			
			}TIM8Bit;
			
		
		}TIM_COMPConfig_t;


typedef struct
{
	
	uint32_t				TIMMode   ;			 /* must be one of TIM_MODE_    */
	TIM_COMPConfig_t		COMPConfig  ;		/* Set Comp configuration for each one */
	TIM1_Prescaller_t		TimPreScaler ;     /* must be one of  TIM_Prescaler_ */
	TIM_Instance_t			Instance ;        /* peripheral select TIM0 or TIM1 */
	uint8_t					TIM_Interrupt ;  /* one of TIM0_INIT_ to enable specific interrupt  */
	
}TIMInit_t;














/* 
 * BRIEF			: this function used to config timer(0/2/1) as a normal mode 
 * PARAM(input)		: TIMConfig pointer to handler that hold all Timer instance configuration 
 * RETVAL(TIM_Status_t)	: TIM status  
 */ 
TIM_Status_t TIM_NormalModeInit(TIMInit_t * TIMConfig );







/* 
 * BRIEF		: this function used to config timer(0/2/1) as out comparator NON PWM mode 
 * PARAM(input)	: TIMConfig used as a pointer to configuration register 
 * RETVAL(TIM_Status_t)	: TIM status  
 */ 
TIM_Status_t TIM_OutCompareModeInit(TIMInit_t * TIMConfig );






/* 
 * BRIEF		: this function used to DE config timer(0/1/2) 
 * PARAM(input)	: TIM_Instance to timer that we will be configure 
 * RETVAL(TIM_Status_t)	: TIM status  
 */ 
TIM_Status_t TIM_DeInit  ( TIM_Instance_t  TIM_Instance );







/* 
 * BRIEF		: this function used to config timer(0/2) as aPWM mode 
 * PARAM(input)	:  TIMConfig  used as a pointer to Timer instance configuration 
 * PARAM(input)	:  Duty cycle take value from (0 t0 100 ) 
 * RETVAL(TIM_Status_t)	: TIM status  
 */ 
TIM_Status_t TIM_PWMMode_SetDuty(TIMInit_t * TIMConfig, uint8_t DutyCycle);







/* 
 * brief : this function used to initialize Timer one as Input Capture mode 
 * parameter(input) : Edge indicate start edge that will start with  
 * return : current timer value 
 */
TIM_Status_t TIM_InputCaptureModeInit( uint8_t Edge  );








/* 
 * brief		: this function used to set Timer counter register 
 * parameter(Input)	: Instance TIM0 or TIM1 or TIM1
 * parameter(Input)	: ContVal used as start timer count value 
 * return : void 
 */
TIM_Status_t TIM_SetValue( TIM_Instance_t	Instance  ,uint8_t  CountVal);








/* 
 * brief : this function used to return current timer value
 * parameter(input) : Instance TIM0 or TIM1 or TIM2 
 * parameter(output) : CountVal Pointer to variable that will receive value 
 * return : TIM Status 
 */
TIM_Status_t TIM_GetValue( TIM_Instance_t	Instance  ,uint8_t * CountVal);








/* 
 * BRIEF		: this function used to start timer with previous configuration  
 * PARAM(input)		: TIMConfig pointer to handler that hold all Timer instance configuration
 * RETVAL(TIM_Status_t)	: TIM status  
 */ 
TIM_Status_t TIM_Start(TIMInit_t * TIMConfig );









/* 
 * BRIEF			: this function used to stop timer clock 
 * PARAM(input)		: TIMConfig pointer to handler that hold all Timer instance configuration
 * RETVAL(TIM_Status_t)	: TIM status  
 */ 
TIM_Status_t TIM_Stop(TIM_Instance_t TIM_Instance);









/* 
 * brief : this function used to initialize TImer Instance as PWM  
 * parameter(input) : TIMConfig Hold all Timer Configuration 
 * return : current timer value 
 */
TIM_Status_t TIM_PWMModeInit(TIMInit_t * TIMConfig );









/* 
 * brief : this function used to set all callback function 
 * parameter(input) : Interrupt_Num indicate which interrupt that you need to set its Call Back fun
 * return : current timer value 
 */
TIM_Status_t TIM_CallBack_FuctionSet(IT_SelBIT_t Interrupt_Num ,  TIMCaLL_BackFun  callbackfunction);











#endif /* TIMER_INTERFACE_H_ */