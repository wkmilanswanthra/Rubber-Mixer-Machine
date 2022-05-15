/*
 * ADC.h
 *
 * Created: 4/13/2021 7:53:01 AM
 *  Author: Achintha
 */ 


#ifndef ADC_H_
#define ADC_H_


#include <avr/io.h>

//initialize ADC
void adc_init();

// read adc value
uint16_t adc_read(uint8_t ch);




#endif /* ADC_H_ */