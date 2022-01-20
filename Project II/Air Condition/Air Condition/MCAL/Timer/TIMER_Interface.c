/*
 * TIMER_Interface.c
 *
 * Created: 1/6/2022 8:20:17 PM
 *  Author: Ahmed_Ayman
 */ 



#include "TIMER_Interface.h"

/* vectors for Timer0 & Timer1 & Timer2 as described in data sheet */
void __vector_4 (void)  __attribute__ ((signal,used));			// TIMER2_COMP VECTOR 
void __vector_5 (void)  __attribute__ ((signal,used));			// TIMER2_OVERFLOW VECTOR
void __vector_6 (void)  __attribute__ ((signal,used));			// TIMER1_COMPTURE VECTOR
void __vector_7 (void)  __attribute__ ((signal,used));			// TIMER1_COMPA VECTOR
void __vector_10 (void) __attribute__ ((signal,used));			// TIMER_COMPB VECTOR
void __vector_11 (void) __attribute__ ((signal,used));			// TIMER_OVERFELOW VECTOR 




/* for timer0 */
PRIVATE TIMCaLL_BackFun COMPMatch0_Fun ;
PRIVATE TIMCaLL_BackFun OverFlow0_Fun ;

/* for timer2 */
PRIVATE TIMCaLL_BackFun COMPMatch2_Fun ;
PRIVATE TIMCaLL_BackFun OverFlow2_Fun ;

/* for timer1 */
PRIVATE TIMCaLL_BackFun	InputCapture_callbackfunction ;
PRIVATE TIMCaLL_BackFun	CompareA_callbackfunction ;
PRIVATE TIMCaLL_BackFun	CompareB_callbackfunction ;
PRIVATE TIMCaLL_BackFun	Overflow_callbackfunction ;




#define SET_REGISTER_VAL(REG , MASK , VAL ){	\
	REG &= ~(MASK) ;							\
	REG |= VAL   ;								\
}

#define FUN_CHECK_PARAM(PARAM) {		\
	if(PARAM == NULL)					\
	{									\
		return TIM_PARAM_ERROR ;		\
	}else										\
	{											\
		;										\
	}											\
}




/* 
 * BRIEF		: this function used to config timer(0/2/1) as out comparator NON PWM mode 
 * PARAM(input)	: TIMConfig used as a pointer to configuration register 
 * RETVAL(TIM_Status_t)	: TIM status  
 */ 
  TIM_Status_t  TIM_OutCompareModeInit(TIMInit_t * TIMConfig )
{
	FUN_CHECK_PARAM(TIMConfig);
	
	
	/* Set Interrupt Enable bits */
	

	
	if(TIMConfig->Instance == TIM0)
	{
		SET_REGISTER_VAL(TCCR0 , TIM8Bit_COMP_OUT_MASK|TIM8Bit_MODE_MASK , TIMConfig->COMPConfig.TIM8Bit.CompAction |(TIM_MODE_CTC>> 0x10));
		OCR0 = TIMConfig->COMPConfig.TIM8Bit.CompValue ;
	}
	else if(TIMConfig->Instance == TIM2)
	{
		SET_REGISTER_VAL(TCCR2 , TIM8Bit_COMP_OUT_MASK|TIM8Bit_MODE_MASK , TIMConfig->COMPConfig.TIM8Bit.CompAction  | (TIM_MODE_CTC>> 0x10) );
		OCR2 = TIMConfig->COMPConfig.TIM8Bit.CompValue ;
		
	}else if(TIMConfig->Instance == TIM2)
	{
			TCCR1A  =  0x00u ;

			if(TIMConfig->COMPConfig.TIM16Bit.CompNum == COMP_A_B_)
			{
				TCCR1A  = TIMConfig->COMPConfig.TIM16Bit.CompAction  << COMP_A_ |TIMConfig->COMPConfig.TIM16Bit.CompAction << COMP_B_  ;
				OCR1A =  TIMConfig->COMPConfig.TIM16Bit.CompValue ;
				OCR1B =  TIMConfig->COMPConfig.TIM16Bit.CompValue ;
				
			}else if(TIMConfig->COMPConfig.TIM16Bit.CompNum == COMP_A_)
			{
				TCCR1A  = TIMConfig->COMPConfig.TIM16Bit.CompAction <<TIMConfig->COMPConfig.TIM16Bit.CompNum  ;
				OCR1A = TIMConfig->COMPConfig.TIM16Bit.CompValue ;

			}else if(TIMConfig->COMPConfig.TIM16Bit.CompNum == COMP_B_)
			{
				TCCR1A  =TIMConfig->COMPConfig.TIM16Bit.CompAction <<TIMConfig->COMPConfig.TIM16Bit.CompNum   ;
				OCR1B = TIMConfig->COMPConfig.TIM16Bit.CompValue ;
				
				}else{
				return TIM_CONFIG_ERROR ;
			}
		
	}else
	{
		return TIM_CONFIG_ERROR ;
	}
	
	_TIM_IT_EN(TIMConfig->TIM_Interrupt) ; 
	return TIM_OK ;


}




/* 
 * BRIEF		: this function used to config timer(0/2/1) as a normal mode 
 * PARAM(input)	: TIMConfig pointer to handler that hold all Timer instance configuration 
 * RETVAL(TIM_Status_t)	: TIM status  
 */ 
  TIM_Status_t TIM_NormalModeInit(TIMInit_t * TIMConfig )
{

	FUN_CHECK_PARAM(TIMConfig);
	
	
	if (TIMConfig->Instance == TIM0)
	{
			TCCR0 = 0;

	}else if (TIMConfig->Instance ==TIM2 )
	{
			TCCR2 = 0;

	}else if (TIMConfig->Instance == TIM1)
	{
			TCCR1A = 0 ;
			TCCR1B = 0 ;

	}else
	{
		
		return TIM_CONFIG_ERROR ; 
	}


	return TIM_OK ;


}


/* 
 * BRIEF		: this function used to DE config timer(0/1/2) 
 * PARAM(input)	: TIM_Instance to timer that we will be configure
 * RETVAL(TIM_Status_t)	: TIM status  
 */ 
  TIM_Status_t TIM_DeInit(TIM_Instance_t TIM_Instance  )
{	
	
	if(TIM_Instance == TIM0)	/* De init Timer 0 */
	{
		TCCR0 = 0 ; 
		TCNT0 = 0 ; 
		OCR0  = 0 ;  
		TIMSK &= ~((1<<OCIE0)|(1<<TOIE0)) ;
		
	}
	else if(TIM_Instance == TIM2)	 /* De init timer 2 */
	{
		TCCR2 = 0 ;
		TCNT2 = 0 ;
		OCR2  = 0 ;
		TIMSK &= ~((1<<OCIE2)|(1<<TOIE2)) ;
	
	}else if(TIM_Instance  == TIM1)	 /* De init Timer 1 */
	{
		TCCR1A = 0 ;
		TCCR1B = 0 ; 
		TCNT1 = 0 ; 
		ICR1 = 0  ; 
		TIMSK &= ~((1<<OCIE1A)|(1<<OCIE1B)|(1<<TICIE1)|(1<<TOIE1));
	
	}else
	{
		return TIM_CONFIG_ERROR ;
	}

	return TIM_OK ; 
}





/* 
 * BRIEF		:this function used to config timer(0/2) as aPWM mode 
 * PARAM(input)	:TIMConfig  used as a pointer to Timer instance configuration 
 * PARAM(input)	:Duty cycle take value from (0 t0 100 ) 
 * RETVAL(TIM_Status_t)	: TIM status  
 */ 
  TIM_Status_t TIM_PWMMode_SetDuty(TIMInit_t * TIMConfig, uint8_t DutyCycle)
{
		FUN_CHECK_PARAM(TIMConfig);
		
		
	if(TIMConfig->Instance == TIM0)
	{
		OCR0 = (256* DutyCycle  )/100;
	}else if(TIMConfig->Instance == TIM2)
	{
		OCR2 = (256 * DutyCycle )/100;
	}else if(TIMConfig->Instance == TIM1)
	{
			ICR1 = 0xfff ;
			if( TIMConfig->COMPConfig.TIM16Bit.CompNum  == COMP_A_B_ )
			{
				OCR1A  = (((TIMConfig->TIMMode  & 0xfff)/100) * DutyCycle )  ;
				OCR1B  = (((TIMConfig->TIMMode  & 0xfff)/100) * DutyCycle )  ;
				
			}else if(  TIMConfig->COMPConfig.TIM16Bit.CompNum == COMP_B_ )
			{
				OCR1B  =((TIMConfig->TIMMode  & 0xfff) * DutyCycle )/100  ;
			}else
			{
				OCR1A  = ((TIMConfig->TIMMode  & 0xfff) * DutyCycle )/100  ;
			}

	}else
	{
		
	}
	
	return TIM_OK ;

}





/* 
 * BRIEF		: this function used to start timer with previous configuration  
 * PARAM(input)	: TIMConfig pointer to handler that hold all Timer instance configuration
 * RETVAL(TIM_Status_t)	: TIM status  
 */ 
  TIM_Status_t TIM_Start(TIMInit_t * TIMConfig )
{
	FUN_CHECK_PARAM(TIMConfig);

		
		
	if(TIMConfig->Instance == TIM0)
	{
		SET_REGISTER_VAL(TCCR0 , TIM_PRESCALLER_MASK ,TIMConfig->TimPreScaler );
	}
	else if(TIMConfig->Instance == TIM2)
	{
		SET_REGISTER_VAL(TCCR2 , TIM_PRESCALLER_MASK , TIMConfig->TimPreScaler );
		
	}else if(TIMConfig->Instance == TIM1)
	{
		SET_REGISTER_VAL(TCCR1B , TIM_PRESCALLER_MASK , TIMConfig->TimPreScaler );
		
	}else{
		
		return TIM_CONFIG_ERROR ;
	}

	return TIM_OK ;
}




/* 
 * BRIEF		: this function used to stop timer clock 
 * PARAM(input)	: TIMConfig pointer to handler that hold all Timer instance configuration
 * RETVAL(TIM_Status_t)	: TIM status  
 */ 



 TIM_Status_t TIM_Stop(TIM_Instance_t TIM_Instance  )
{

		
	
	if(TIM_Instance == TIM0)
	{
		SET_REGISTER_VAL(TCCR0 , TIM_PRESCALLER_MASK , 0x00u );
	}
	else if(TIM_Instance == TIM2)
	{
		SET_REGISTER_VAL(TCCR2 , TIM_PRESCALLER_MASK , 0x00u );
		
	}else if(TIM_Instance == TIM1)
	{
		SET_REGISTER_VAL(TCCR1B , TIM_PRESCALLER_MASK , 0x00u );
		
	}else{

		return TIM_CONFIG_ERROR ;
	}

	return TIM_OK ;
}







/* 
 * brief		: this function used to set Timer counter register 
 * parameter(Input)	: Instance TIM0 or TIM1 or TIM1
 * parameter(Input)	: ContVal used as start timer count value 
 * return : void 
 */
  TIM_Status_t TIM_SetValue( TIM_Instance_t	Instance ,uint8_t CountVal)
{
	if(Instance == TIM0)
	{
		TCNT0 = CountVal ; 
	}
	else if(Instance == TIM2)
	{
		TCNT2 = CountVal ; 
		
	}else if(Instance == TIM1)
	{
		TCNT1 = CountVal ; 
		
	}else
	{
		return TIM_CONFIG_ERROR ;
	}
	

	return TIM_OK ;

}







/* 
 * brief : this function used to return current timer value
 * parameter(input) : Instance TIM0 or TIM1 or TIM2 
 * parameter(output) : CountVal Pointer to variable that will receive value 
 * return : TIM Status 
 */
  TIM_Status_t TIM_GetValue( TIM_Instance_t	Instance  ,uint8_t * CountVal)
{
	if(CountVal == NULL)
	{
		return TIM_PARAM_ERROR ; 
	}
	
	
	
	if(Instance == TIM0)
	{
		*CountVal = TCNT0   ;
	}
	else if(Instance == TIM2)
	{
		*CountVal = TCNT2  ;
		
	}else if(Instance == TIM1)
	{
		*CountVal = TCNT1 ; 
	}else
	{
		return TIM_CONFIG_ERROR ;
	}
	

	return TIM_OK ;



}


/* 
 * brief : this function used to initialize TImer Instance as PWM  
 * parameter(input) : TIMConfig Hold all Timer Configuration 
 * return : current timer value 
 */
TIM_Status_t	TIM_PWMModeInit(TIMInit_t * TIMConfig )
{
	FUN_CHECK_PARAM(TIMConfig);
	
	
	if (TIMConfig->Instance == TIM1)
	{
		if(TIMConfig->TIMMode & 0x1000)
		{
			if( TIM_MODE_16Bit_MODE_COMP_PWM_FAST_8B == (TIMConfig->TIMMode&0xffff ))
			{
				TCCR1A  =  0x01u ;
				TCCR1B  =  0x01u<<3 ;
			}
			else if(TIM_MODE_16Bit_MODE_COMP_PWM_FAST_9B == (TIMConfig->TIMMode&0xffff))
			{
				TCCR1A  =  0x02u ;
				TCCR1B  =  0x01u<<3 ;
			}
			else if( TIM_MODE_16Bit_MODE_COMP_PWM_FAST_10B == (TIMConfig->TIMMode&0xffff))
			{
				TCCR1A  =  0x03u ;
				TCCR1B  =  0x01u<<3 ;
			}
			else if( TIM16Bit_MODE_COMP_PWM_FAST_MODE == (TIMConfig->TIMMode&0xffff ))
			{
				TCCR1A  =  0x02u ;
				TCCR1B  =  0x03u<<3 ;
			}else{
				
				
				
				
			}
			
		
			if(TIMConfig->TIM_Interrupt != 0)
			{
				_TIM_IT_EN(TIMConfig->TIM_Interrupt) ;
			}
		}else
		{
			/* TIM16Bit_MODE_COMP_PWM_PHASE_CORRECT */
			if( TIMConfig->TIMMode  & 0x2000)
			{
				TCCR1A  =   0x02u ;
				TCCR1B  =   0x02u << 3 ;
			}
			else if( TIMConfig->TIMMode  & 0x4000)
			{
				TCCR1A  =  0x01u ;
				TCCR1B  =  0x02u << 3 ;
			}

		}
		
		
		
		if(TIMConfig->COMPConfig.TIM16Bit.CompNum == COMP_A_B_)
		{
			TCCR1A  |= TIMConfig->COMPConfig.TIM16Bit.CompAction << COMP_A_ |TIMConfig->COMPConfig.TIM16Bit.CompAction << COMP_B_  ;
		}else
		{
			TCCR1A  |= TIMConfig->COMPConfig.TIM16Bit.CompAction <<   TIMConfig->COMPConfig.TIM16Bit.CompNum  ;
		}
	}
	else if ((TIMConfig->Instance == TIM0)|| (TIMConfig->Instance == TIM2))
	{
			
			if(TIMConfig->Instance == TIM0)
			{
				SET_REGISTER_VAL(TCCR0 , TIM8Bit_COMP_OUT_MASK|TIM8Bit_MODE_MASK , TIMConfig->COMPConfig.TIM8Bit.CompAction |(TIMConfig->TIMMode >> 0x10 ) );
				OCR0 = TIMConfig->COMPConfig.TIM8Bit.CompValue ;
			}
			else if(TIMConfig->Instance == TIM2)
			{
				SET_REGISTER_VAL(TCCR2 , TIM8Bit_COMP_OUT_MASK|TIM8Bit_MODE_MASK , TIMConfig->COMPConfig.TIM8Bit.CompAction  | (TIMConfig->TIMMode >> 0x10 ) );
				OCR2 = TIMConfig->COMPConfig.TIM8Bit.CompValue ;
				
			}
		
		}else{
		
		return TIM_CONFIG_ERROR ;
	}
	
	
	if(TIMConfig->TIM_Interrupt != TIM_IT_DIS)
	{
		_TIM_IT_EN(TIMConfig->TIM_Interrupt) ;
	}
	
	
	
	return TIM_OK ;

}



/* 
 * brief : this function used to initialize Timer one as Input Capture mode 
 * parameter(input) : Edge indicate start edge that will start with  
 * return : current timer value 
 */
TIM_Status_t TIM_InputCaptureModeInit( uint8_t Edge  )
{
	
	SET_REGISTER_VAL(TCCR1B , TIM16Bit_InputCapture_CAPTURE_EDGE_MASK , Edge ) ;
	
	return TIM_OK ;
	
}











/* 
 * brief : this function used to set all callback function 
 * parameter(input) : Interrupt_Num indicate which interrupt that you need to set its Call Back fun
 * return : current timer value 
 */
  TIM_Status_t TIM_CallBack_FuctionSet(IT_SelBIT_t Interrupt_Num ,  TIMCaLL_BackFun  callbackfunction)
{
	
	if (callbackfunction == NULL)
	{
		return TIM_PARAM_ERROR ;
	}
	
	switch(Interrupt_Num)
	{
		case TIM_0_IT_COMP :
				COMPMatch0_Fun = callbackfunction ;
		break ;
		case  TIM_0_IT_OVER :
				OverFlow0_Fun = callbackfunction ;
		break; 
		case TIM_2_IT_COMP :
				COMPMatch2_Fun = callbackfunction ;
		
		break; 
		case TIM_2_IT_OVER :
				OverFlow2_Fun = callbackfunction ;
		
		break ;
		case TIM_1_IT_CAPT :
						InputCapture_callbackfunction = callbackfunction ;
		break; 
		case  TIM_1_IT_OVER :
						Overflow_callbackfunction = callbackfunction ;
		break; 
		case  TIM_1_IT_COMPA :
						CompareA_callbackfunction = callbackfunction ;
		break; 
		case  TIM_1_IT_COMPB :
						CompareB_callbackfunction = callbackfunction ;
		break; 
		default:
		
			return TIM_CONFIG_ERROR ;
		break; 
		
		
	}
	
	


	return TIM_OK ; 
	
}







void __vector_6(void )	 // timer1 input capture interrupt number
{
	InputCapture_callbackfunction();
}

void __vector_7(void )		// timer1 CompareA
{
	CompareA_callbackfunction();
}
void __vector_8(void )	 // timer1 compareB interrupt number
{
	CompareB_callbackfunction();
}

void __vector_9(void )		// timer1 overflow
{
	Overflow_callbackfunction() ;
}



/* all vectors specific for timer2 and timer0 */
void __vector_10(void)
{
	COMPMatch0_Fun();
}
void __vector_11(void)
{
	OverFlow0_Fun();
}


void __vector_4(void)
{
	COMPMatch2_Fun();
}
void __vector_5(void)
{
	OverFlow2_Fun();
}