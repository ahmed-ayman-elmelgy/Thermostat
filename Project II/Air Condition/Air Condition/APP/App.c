/*
 * App.c
 *
 * Created: 1/17/2022 8:33:34 PM
 *  Author: Ahmed_Ayman
 */ 

#include "App.h"
#include "stdbool.h"

#define Step_Size			0x05u
App_Handler_t App_Handler ;
uint8_t Config_Flag = 1  ;
static uint8_t LM35_GetTemp(void);
static void IT_Num0_Init(void);
static int8_t Display_Screen(uint8_t * Mode);



void App_Init(void){
	Motor_Init();
	ADC_Init(ADC_PRESC_8 , ADC_VREF_VCC_INT) ;
	LCD_init();
	LCD_displayStringRowColumn(1,5,"Welcome");
	IT_Num0_Init();
	_delay_ms(1000);
	LCD_clearScreen();
}

uint8_t LM35_GetTemp(void){
	uint16_t ADC_Data =	ADC_Read(ADC_CH0);
	return ((( ADC_Data )* 0.0048828 )/0.01) ;
}



void IT_Num0_Init(void){	
	MCUCSR	|= 1<<ISC2 ;
	GICR	|= (1<<INT2) ;
	DDRB |= 0xc0 ;
	sei();
}

	uint8_t User_Input = 0 ;
	 
int8_t Display_Screen(uint8_t * Mode){
	if (Mode == NULL){
		return -1;
	}
	LCD_displayStringRowColumn(0,0 ,Mode);
	LCD_displayStringRowColumn(0,9 , "TEMP");
	LCD_goToRowColumn(0,14);
	LCD_intgerToString(App_Handler.Current_Temp );
	LCD_displayStringRowColumn(1,9 , "SET");
	LCD_goToRowColumn(1,14);
	LCD_intgerToString(App_Handler.Low_Temp );
}
void App_Update(void){
	while(Config_Flag == 1){// Config mode loop
		App_Handler.Current_Temp = LM35_GetTemp();
		Display_Screen("Config");
		if (App_Handler.Low_Temp < 10){
			LCD_goToRowColumn(1,15);
			LCD_displayCharacter(" ");
		}
		User_Input = KeyPad_getPressedKey();			
		switch(User_Input)
		{
			case   1 : {/* handling - operation */
					
				if (App_Handler.Low_Temp > 0 ){
					App_Handler.Previous_Temp = App_Handler.Low_Temp-- ;
				}
			}
			break; 
				
				
			case 2: {/* handling + operation */ 
					App_Handler.Previous_Temp =  ++App_Handler.Low_Temp ;	
			}
			break;  
			default:
				User_Input = 0  ;
			break; 
				
		}
	}
	
	LCD_sendCommand(0x01);
	while(!Config_Flag)// Normal mode 
	{
		
		App_Handler.Current_Temp = LM35_GetTemp();
		if ((App_Handler.Current_Temp <= App_Handler.Low_Temp)){
			Motor_Dir(DID_STOP , 0);
		}else if (App_Handler.Current_Temp > 100){
			LCD_displayStringRowColumn(0,14 , "99");
			Motor_Dir(DIR_FORWARD , 100);
		}
		else{
			Motor_Dir(DIR_FORWARD ,App_Handler.Current_Temp );
			App_Handler.Previous_Temp = App_Handler.Current_Temp ;
		}
		if (App_Handler.Current_Temp < 100)
		{
			Display_Screen("NORMAL");
		}
		
		if (App_Handler.Current_Temp < 10){
			LCD_goToRowColumn(0,15);
			LCD_displayCharacter(" ");
		}
	}
}



ISR(INT2_vect)
{

			if(Config_Flag == 0)
			{ 
				Config_Flag = 1 ;
				
			}else
			{
				
				Config_Flag = 0 ; 
			}
		
		
	
	Motor_Dir(DID_STOP , 0) ;
	PORTB ^= 0x40;

}

