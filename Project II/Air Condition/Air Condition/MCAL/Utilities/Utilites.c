/*
 * Utilites.c
 *
 * Created: 1/6/2022 6:28:15 PM
 *  Author: Ahmed_Ayman
 */ 

#include "Utilites.h"

# define SOFTWARE_PWM_CTC_MODE			1



PRIVATE void Delay_CallBack(void);


/* prototypes for Local software PWM CallBack functions */
PRIVATE void PWM_Toggle_Timer0(void);
PRIVATE void PWM_Toggle_Timer1(void);
PRIVATE void PWM_Toggle_Timer2(void);
PRIVATE GPIO_InitTypeDef   PWMTim0_PIN , PWMTim1_PIN , PWMTim2_PIN;
PRIVATE GPIO_TypeDef* PWMTim0_PORT , * PWMTim1_PORT , * PWMTim2_PORT;
 
 
 #if SOFTWARE_PWM_CTC_MODE
 PRIVATE uint8_t Duty_TIM0  , Duty_TIM2 ;
#endif
 PRIVATE uint16_t Duty_TIM1; 

/* 
 * brief : this function used to generate delay in Ms blocking mode 
 * parameter : Instance TIM0 or TIM2 
 * parameter : UsDelay Delay in Us 
 * return : current timer status 
*/

PRIVATE uint16_t  u8_NumOFms ;
PRIVATE DelayConfig_t str_Delay; 
static  TIMInit_t *  Tim_Delay_Handler ;
static uint8_t IN_Use = 0 ;


Utilies_Status_t Utilites_DelayMs_IT(TIMInit_t *  Tim_Handler, uint16_t MsDelay , DalayType_t Dalay_type , TIMCaLL_BackFun callbackfunction)
{		
	
		if(IN_Use == 1)
		{
			return UTIL_PARAM_ERROR ; 
		}
		
		if((Tim_Handler == NULL) ||(callbackfunction == NULL))
		{
			return UTIL_PARAM_ERROR ;
		}
		
		Tim_Delay_Handler = Tim_Handler ;
		Tim_Delay_Handler->Instance = TIM2 ;
		if(TIM_DeInit(TIM2)	!= TIM_OK)
		{
			return UTIL_TIM_ERROR ;
		}else
		{
			;
		}
		if(TIM_OutCompareModeInit(Tim_Delay_Handler)	!= TIM_OK)
		{
			return UTIL_TIM_ERROR ;
		}else
		{
			;
		}
		
		if(TIM_CallBack_FuctionSet(Tim_Delay_Handler->TIM_Interrupt ,Delay_CallBack )!= TIM_OK)
		{
			return UTIL_TIM_ERROR ;
		}else
		{
			;
		}
		/* set shared variable */
		str_Delay.Delaycallbackfunction= callbackfunction ;
		str_Delay.MsDelay = MsDelay;
		u8_NumOFms = MsDelay;
		str_Delay.DelayAttr = Dalay_type;
		if(TIM_Start(Tim_Delay_Handler) != TIM_OK)
		{
			return  UTIL_TIM_ERROR ; 
		}else
		{
			;
		}
		IN_Use =1 ;
		return UTIL_OK ; 

}







/* 
 * brief : this function used to generate delay in Ms blocking mode accuracy 96% 
 * parameter : UsDelay Delay in Us 
 * return : current timer status 
*/

Utilies_Status_t Utilites_DelayUs(uint8_t TimerInstance  ,  uint16_t UsDelay)
{
	uint16_t TotalTicks = (uint16_t)((F_CPU)/(1000000)) * UsDelay ; 
	uint16_t TotalLoops = TotalTicks / 256 ;

	if(TimerInstance == TIM0)	/* if waiting is less than one complete overflow */
	{
		TCCR0 = TIM_0_Prescaler_1 ;
		if (TotalLoops == 0 )
		{
			OCR0  = TotalTicks ;	/* SET ocr register to required value */
			TCNT0 = 0;
			while(!(TIFR &(1<<OCF0)));
			TIFR |= 1<<OCF0;
			
		}else{
			
			
			OCR0 = 255 ; 
			for(uint16_t ietrator=0;ietrator<TotalLoops ;ietrator++)
			{
				TCNT0 =0;
				while(!(TIFR &(1<<OCF0)));
				TIFR |= 1<<OCF0;
			}
		}
	}
	else if(TimerInstance == TIM2)
	{
		TCCR2 = TIM_2_Prescaler_8 ;
		OCR2 = (uint8_t)((F_CPU)/(1000000));	/* SET ocr register to required value */
		for(uint16_t ietrator=2;ietrator<TotalLoops/2;ietrator++)
		{
			TCNT2 =0;
			while(!(TIFR &(1<<OCF2)));
			TIFR |= 1<<OCF2 ;
		}
	}else
	{
		return UTIL_PARAM_ERROR ; 
	}
	


return UTIL_OK ;

}


 
/*
 * brief :	 this function used to inti all Timers in PWM Mode with selected Mode 
 *			 selected mode must be one of Macros that started with( TIM_MODE_  )
 * Param (Input) : PORT pointer to GPIO port 
 * Param (input) : PIN_Num Pin number in selected port 
 * Param (input) : Tim_PWM_Handler {Pointer to timer configuration register 
 * Return : Utilies_Status_t typedef to Status 
 */
Utilies_Status_t Software_PWM_Init( StrGPIO_t PORT , uint8_t PIN_Num ,TIMInit_t * Tim_PWM_Handler )
{
	
	if(Tim_PWM_Handler == NULL)
	{
		return UTIL_PARAM_ERROR ;
	}else
	{
		;
	}


	
	
	
	#if SOFTWARE_PWM_CTC_MODE
	Tim_PWM_Handler->TIMMode = TIM_MODE_CTC ;
	#else 
	Tim_PWM_Handler->TIMMode = TIM_MODE_COMP_PWM_FAST ;
	#endif
	

	if (Tim_PWM_Handler->Instance == TIM1)
	{
		Tim_PWM_Handler->TIMMode = TIM_MODE_CTC ;
	}else
	{
		;
	}
	TIM_PWMModeInit(Tim_PWM_Handler) ;
	
	if (Tim_PWM_Handler->Instance  == TIM0)
	{
		PWMTim0_PIN.mode = GPIO_MODE_OUTPUT ;
		PWMTim0_PIN.pin = PIN_Num ;
		PWMTim0_PIN.pull = GPIO_NOPULL ;
		HAL_GPIO_INIT_PIN( PORT , &PWMTim0_PIN );
		
		PWMTim0_PORT = PORT ;
		#if !SOFTWARE_PWM_CTC_MODE
		_TIM_IT_EN(TIM_0_IT_OVER);
		#endif
		TIM_CallBack_FuctionSet(TIM_0_IT_OVER , PWM_Toggle_Timer0); 
		TIM_CallBack_FuctionSet(Tim_PWM_Handler->TIM_Interrupt , PWM_Toggle_Timer0);

	}else if (Tim_PWM_Handler->Instance == TIM1)
	{	
		PWMTim1_PIN.mode = GPIO_MODE_OUTPUT ;
		PWMTim1_PIN.pin = PIN_Num ;
		PWMTim1_PIN.pull = GPIO_NOPULL ;
		HAL_GPIO_INIT_PIN( PORT , &PWMTim1_PIN );
		PWMTim1_PORT = PORT ;
		TIM_CallBack_FuctionSet(Tim_PWM_Handler->TIM_Interrupt , PWM_Toggle_Timer1);
	}else if(Tim_PWM_Handler->Instance == TIM2)
	{	
		PWMTim2_PIN.mode = GPIO_MODE_OUTPUT ;
		PWMTim2_PIN.pin = PIN_Num ;
		PWMTim2_PIN.pull = GPIO_NOPULL ;
		HAL_GPIO_INIT_PIN( PORT , &PWMTim2_PIN );	
		PWMTim2_PORT = PORT ;
		#if !SOFTWARE_PWM_CTC_MODE
		_TIM_IT_EN(TIM_2_IT_OVER);
		#endif
		TIM_CallBack_FuctionSet(TIM_2_IT_OVER , PWM_Toggle_Timer2);
		TIM_CallBack_FuctionSet(Tim_PWM_Handler->TIM_Interrupt , PWM_Toggle_Timer2);
		
	}else
	{
		return UTIL_TIM_ERROR ;
	}
	
		
	
	
	return  UTIL_OK ; 
	
}



Utilies_Status_t Software_PWM_Start (TIMInit_t * TIMConfig )
{
	
	if(TIMConfig == NULL)
	{
		return UTIL_PARAM_ERROR ;
	}else
	{
		;
	}
	
	TIM_Start(TIMConfig) ;
	return UTIL_OK ;

}




/* 
 * brief : this function used to start timer with given configuration (prescaller)
 * param (input): Tim_PWM_Handler pointer to selected timer configuration that contain Prescaller 
 * param (input): SetDuty desired Duty cycle From (0 t0 100 )
 * return : Utilies_Status_t status 
*/
Utilies_Status_t Software_PWM_UpdateDuty( uint8_t SetDuty  ,TIMInit_t * Tim_PWM_Handler )
{
		if (Tim_PWM_Handler == NULL)
		{
			return UTIL_PARAM_ERROR ;
			}else
			{
				 if(TIM_Stop(Tim_PWM_Handler->Instance) == TIM_OK)
				 {
	
						if(TIM_PWMMode_SetDuty(Tim_PWM_Handler , SetDuty) == TIM_OK)
						{
							if(TIM_Start(Tim_PWM_Handler) == TIM_OK)
							{
								;
							}
							else
							{
								return UTIL_TIM_ERROR ;
							}
						}
						else
						{
							return UTIL_TIM_ERROR ;
						}
					}
					else
					{
						return UTIL_TIM_ERROR ; 
					}
			}
			
		
			
			
			if (Tim_PWM_Handler->Instance == TIM1)
			{
					Duty_TIM1 =((Tim_PWM_Handler->TIMMode & 0xfff)/(100.0 * SetDuty ));
			}
			#if SOFTWARE_PWM_CTC_MODE
			else if (Tim_PWM_Handler->Instance == TIM0)
			{
				  Duty_TIM0 = (256*(SetDuty/100.0));
			}else if (Tim_PWM_Handler->Instance == TIM2)
			{
				 Duty_TIM2 = (uint8_t)(256 * (SetDuty/100.0) );
			}else
			{
				return UTIL_TIM_ERROR ;
			}
			#endif 
			
		
		return UTIL_OK ; 
}

/* 
 * brief : this function used to Stop PWM Operation 
 * param (input): Tim_PWM_Handler pointer to selected timer configuration that contain Prescaller 
 * param (input): SetDuty desired Duty cycle From (0 t0 100 )
 * return : Utilies_Status_t status 
*/
Utilies_Status_t Software_PWM_Stop(TIMInit_t * Tim_PWM_Handler)
{
	
	if(Tim_PWM_Handler == NULL)	 // before any thing you need to check on all Given Parameter 
	{
		return UTIL_PARAM_ERROR ; 
	}else
	{
		;
	}

	if(TIM_Stop(Tim_PWM_Handler->Instance) == TIM_OK)
	{
		return UTIL_TIM_ERROR ;
	}
	else
	{
		return UTIL_TIM_ERROR ;
	}
	
	return UTIL_OK ; 
}








#if SOFTWARE_PWM_CTC_MODE 
/* local function used as Callback To Toggle Selected Pin with Desired GPIO */


void PWM_Toggle_Timer0(void)
{	
	
	static uint8_t ON = 0 ;
	if (Duty_TIM0 == 0 )
	{
		;
	}
	else if(ON == 0 )
	{
		HAL_GPIO_WRITEPIN(PWMTim0_PORT , PWMTim0_PIN.pin , GPIO_PIN_RESET);
		OCR0 = Duty_TIM0 ;
		ON = 1 ;
		
	}
	else
	{
		HAL_GPIO_WRITEPIN(PWMTim0_PORT , PWMTim0_PIN.pin , GPIO_PIN_SET);
		OCR0 = 255 - Duty_TIM0 ;
		ON = 0 ;
	}
}

void PWM_Toggle_Timer2(void)
{
	static uint8_t ON = 0 ; 
	if (Duty_TIM2 == 0 )
	{
		;
	}
	else if(ON == 0 )
	{
		HAL_GPIO_WRITEPIN(PWMTim2_PORT , PWMTim2_PIN.pin , GPIO_PIN_RESET);
		OCR2 = Duty_TIM2 ;
		ON = 1 ;
		
	}else
	{
		HAL_GPIO_WRITEPIN(PWMTim2_PORT , PWMTim2_PIN.pin , GPIO_PIN_SET);
		OCR2 = 255 - Duty_TIM2 ;
		ON = 0 ;
	}

}



#else

void PWM_Toggle_Timer0(void)
{
	HAL_GPIO_TOGGLE_PIN(PWMTim0_PORT , PWMTim0_PIN.pin);
}

void PWM_Toggle_Timer2(void)
{
	HAL_GPIO_TOGGLE_PIN(PWMTim2_PORT , PWMTim2_PIN.pin);
}
#endif 


void PWM_Toggle_Timer1(void)
{
	static uint8_t ON = 0 ;
	if(ON == 0 )
	{
		
		OCR1A =0xfffu - Duty_TIM1 ;
		ON = 1 ;
		
	}
	else
	{
		OCR1A =  Duty_TIM1 ;
		ON = 0 ;
	}
	if(Duty_TIM1 != 0 )
	{
		HAL_GPIO_TOGGLE_PIN(PWMTim1_PORT , PWMTim1_PIN.pin);
	}
}





/* 
 * brief :	callBack Function that handle once OR periodic mode 
 *			this function static function  and called by this driver  
 * Param  : void  
 * Return : void 
 */
void Delay_CallBack(void)
{
	
	--u8_NumOFms;
	if(u8_NumOFms == 1)
	{	
		IN_Use = 0 ; 
		str_Delay.Delaycallbackfunction();
		u8_NumOFms = str_Delay.MsDelay ;
		
		
		if(str_Delay.DelayAttr == Delay_Once)
		{	

			TIMSK &= ~(Tim_Delay_Handler->TIM_Interrupt) ;
		}
		
	}
	
	
	TIFR |= (1<<OCF2);		// clear timer flag 

}