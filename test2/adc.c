/*
 * ADC.c
 *
 * Created: 4/13/2021 7:35:20 AM
 * 
 */ 

#include "ADC.h"

void adc_init()
{
	// AREF = AVcc
	ADMUX = (1<<REFS0);

	// ADC Enable and prescaler of 128.
	
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	
	
}

// read adc value
uint16_t adc_read(uint8_t ch)
{
	// select the corresponding channel 0~7
	
	ch &= 0b00000111;  // AND operation with 7. select 3rd chanal
	ADMUX = (ADMUX & 0xF8)|ch; //0b11111000   0b00000111

	// start single conversion
	// write '1' to ADSC
	ADCSRA |= (1<<ADSC);

	// wait for conversion to complete
	// ADSC becomes '0' again
	
	while(ADCSRA & (1<<ADSC)); //conversion ends when ADSC become 0.

	return (ADC);
}