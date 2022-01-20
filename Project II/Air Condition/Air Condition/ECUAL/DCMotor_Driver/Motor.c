/*
 * Motor.c
 *
 * Created: 1/17/2022 10:24:01 AM
 *  Author: Ahmed_Ayman
 */ 


#include "Motor.h"

#define TIM1_IN_USE				0
#define TIM2_IN_USE				1
#define TIM0_IN_USE				0

static void Motor_CW(uint8_t Motor_num);
static void Motor_ACW(uint8_t Motor_num);
static void Motor_Stop(uint8_t Motor_num);




static MotorSelect_t MOTORS ={	.Motor[MOTOR_1].Pin[0] = GPIO_PIN_2 , .Motor[MOTOR_1].Port[0] = GPIOD ,
								.Motor[MOTOR_1].Pin[1] = GPIO_PIN_3 , .Motor[MOTOR_1].Port[1] = GPIOD ,
								.Motor[MOTOR_2].Pin[0] = GPIO_PIN_5 , .Motor[MOTOR_2].Port[0] = GPIOD ,
								.Motor[MOTOR_2].Pin[1] = GPIO_PIN_5 , .Motor[MOTOR_2].Port[1] = GPIOD , } ;

#if TIM1_IN_USE
static TIMInit_t  Tim_PWM_Handler ={ .Instance = TIM1 ,.COMPConfig.TIM16Bit.CompAction = TIM_COMP_PIN_OUT_Normal  , .COMPConfig.TIM16Bit.CompNum = COMP_A_ , .TIM_Interrupt = TIM_1_IT_COMPA ,.TimPreScaler = TIM_1_Prescaler_1  };


#elif TIM2_IN_USE
static TIMInit_t  Tim_PWM_Handler ={ .Instance = TIM2 ,.COMPConfig.TIM8Bit.CompAction = TIM_COMP_PIN_OUT_Normal   , .TIM_Interrupt = TIM_2_IT_COMP ,.TimPreScaler = TIM_2_Prescaler_1024 };

#elif TIM0_IN_USE
static TIMInit_t  Tim_PWM_Handler ={ .Instance = TIM0 ,.COMPConfig.TIM8Bit.CompAction = TIM_COMP_PIN_OUT_Normal   , .TIM_Interrupt = TIM_0_IT_COMP ,.TimPreScaler = TIM_0_Prescaler_256 };
#endif


MOTOR_STATUS_t Motor_Init(void)
{
		GPIO_InitTypeDef   PIN_CONFIG = {.mode = GPIO_MODE_OUTPUT , .pull = GPIO_NOPULL }; 
		if(Software_PWM_Init( GPIOD , GPIO_PIN_4 ,  &Tim_PWM_Handler ) != UTIL_OK)
		{
			return MOTOR_PWM_ERROR ; 
		}
		if (Software_PWM_Start (&Tim_PWM_Handler) != UTIL_OK)
		{
			return MOTOR_PWM_ERROR ; 
		}
		if (Software_PWM_UpdateDuty(0 , &Tim_PWM_Handler) != UTIL_OK)
		{
			return MOTOR_PWM_ERROR ;
		}
		
		
		for (uint8_t iter = 0 ; iter < Total_MOTORS ; iter++)
		{
			PIN_CONFIG.pin = MOTORS.Motor[MOTOR_1].Pin[0];
			HAL_GPIO_INIT_PIN(MOTORS.Motor[MOTOR_1].Port[0] , &PIN_CONFIG);
			PIN_CONFIG.pin = MOTORS.Motor[MOTOR_1].Pin[1];
			HAL_GPIO_INIT_PIN(MOTORS.Motor[MOTOR_1].Port[1] , &PIN_CONFIG);
		}
	
	return MOTOR_OK ; 
}


MOTOR_STATUS_t Motor_Dir(Motor_DIR_t DIR , uint8_t Speed )
{
	static	uint8_t Motor_Speed = 0 ;
	static	Motor_DIR_t Motor_Dir = DID_STOP ;
	
	if ((Motor_Speed == Speed)&&(Motor_Dir == DIR))
	{
		return MOTOR_OK ; 
	}
	
	switch(DIR)
	{
		case DID_STOP :
			Motor_Stop(MOTOR_1);
			Motor_Stop(MOTOR_2);
			Motor_Dir = DID_STOP ; 
			Motor_Speed = 0 ;

			Software_PWM_UpdateDuty( 0 ,&Tim_PWM_Handler );
		break; 
		case  DIR_BACKWARD :
			Motor_ACW(MOTOR_1);
			Motor_ACW(MOTOR_2);
			Motor_Dir = DIR_BACKWARD ;
			Motor_Speed = Speed ;
			Software_PWM_UpdateDuty( Speed ,&Tim_PWM_Handler );
		break; 
		case  DIR_FORWARD :
			Motor_CW(MOTOR_1);
			Motor_CW(MOTOR_2);
			Motor_Dir = DIR_FORWARD ;
			Motor_Speed = Speed ;
			Software_PWM_UpdateDuty( Speed ,&Tim_PWM_Handler );
		break; 
		case  DIR_LEFT :
			Motor_CW(MOTOR_1);
			Motor_ACW(MOTOR_2);
			Motor_Dir = DIR_LEFT ;
			Motor_Speed = Speed ;
			Software_PWM_UpdateDuty( Speed ,&Tim_PWM_Handler );
		break; 
		case DIR_RIGHT :
			Motor_ACW(MOTOR_1);
			Motor_CW(MOTOR_2);
			Motor_Dir = DIR_RIGHT ;
			Motor_Speed = Speed ;
			Software_PWM_UpdateDuty( Speed ,&Tim_PWM_Handler );
		break; 
		default:
		
		
		break; 
		
		
	}
	
	return MOTOR_OK ;
	
}

static void Motor_ACW(uint8_t Motor_num)
{
	HAL_GPIO_WRITEPIN(MOTORS.Motor[Motor_num].Port[0] , MOTORS.Motor[Motor_num].Pin[0] , GPIO_PIN_SET);
	HAL_GPIO_WRITEPIN(MOTORS.Motor[Motor_num].Port[1] , MOTORS.Motor[Motor_num].Pin[1] , GPIO_PIN_RESET);
}


static void Motor_CW(uint8_t Motor_num)
{
	
	HAL_GPIO_WRITEPIN(MOTORS.Motor[Motor_num].Port[0] , MOTORS.Motor[Motor_num].Pin[0] , GPIO_PIN_RESET);
	HAL_GPIO_WRITEPIN(MOTORS.Motor[Motor_num].Port[1] , MOTORS.Motor[Motor_num].Pin[1] , GPIO_PIN_SET);	
}


static void Motor_Stop(uint8_t Motor_num)
{
	HAL_GPIO_WRITEPIN(MOTORS.Motor[Motor_num].Port[0] , MOTORS.Motor[Motor_num].Pin[0] , GPIO_PIN_RESET);
	HAL_GPIO_WRITEPIN(MOTORS.Motor[Motor_num].Port[1] , MOTORS.Motor[Motor_num].Pin[1] , GPIO_PIN_RESET);
}



