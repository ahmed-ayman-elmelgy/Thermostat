#include "ADC.h"
#include "ADC_Private.h"

void      	ADC_Init	(ADC_Presc_t Prescaler, ADC_Vref_t V_Ref)
{
	ADC.Selections.ADC_Vref   = V_Ref;
	ADC.Control.prescalar     = Prescaler;
	ADC.Control.ADC_enable    = 1;
}

uint16_t 	ADC_Read	(ADC_Channel_t channel)
{
	ADC.Selections.channel = channel;
	ADC.Control.start_conv = 1;
	while(ADC.Control.start_conv == 1);
	return ADC.Data;
}
