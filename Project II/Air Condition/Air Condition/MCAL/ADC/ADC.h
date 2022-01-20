#ifndef ADC_H_
#define ADC_H_


#include "ADC_Cfg.h"


void      	ADC_Init	(ADC_Presc_t Prescaler, ADC_Vref_t V_Ref);
uint16_t  	ADC_Read    (ADC_Channel_t Channel);

#endif /* ADC_H_ */