#ifndef ADC_CFG_H_
#define ADC_CFG_H_

#include <stdint.h>

typedef enum
{
	ADC_PRESC_2 = 1,
	ADC_PRESC_4,
	ADC_PRESC_8,
	ADC_PRESC_16,
	ADC_PRESC_32,
	ADC_PRESC_64,
	ADC_PRESC_128
}ADC_Presc_t;

typedef enum
{
	ADC_VREF_External,
	ADC_VREF_VCC_INT,
	ADC_VREF_V2_56_INT = 3
}ADC_Vref_t;

typedef enum
{
	ADC_CH0,
	ADC_CH1,
	ADC_CH2,
	ADC_CH3,
	ADC_CH4,
	ADC_CH5,
	ADC_CH6,
	ADC_CH7
}ADC_Channel_t;


#endif /* ADC_CFG_H_ */