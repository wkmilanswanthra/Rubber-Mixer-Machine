/*
 * Stepper_motors.h
 *
 * Created: 12/4/2021 1:53:46 PM
 *  Author: Githmi Paranahewa
 */ 

#include <avr/io.h> /* Include AVR std. library file */
#include <util/delay.h> /* Include delay header file */

#define STPRTrayPsh_PRT PORTC	
#define STPRTrayPsh_DDR DDRC	
#define STPRTrayPsh_PIN PINC	

#define STPRMix_PRT PORTD
#define STPRMix_DDR DDRD
#define STPRMix_PIN PIND

void stprTrayPsh_init();
void stprMix_init();
void stprTrayPsh_clk(int);
void stprTrayPsh_aclk(int);
void stprMix_clk(int);
void stprMix_aclk(int);




//Stepper Motor functions
void stprTrayPsh_init(){
	STPRTrayPsh_DDR |= 0xFF;
	STPRTrayPsh_PRT &= 0x0F;
	
}
void stprMix_init(){
	STPRMix_DDR = 0xFF;
	STPRMix_PRT = 0X00;
	
}
/*Push Action*/
void stprTrayPsh_clk(int cycles){
	
	const unsigned int period= 6;
	for(int i=0;i<cycles;i++)
	{	STPRTrayPsh_PRT = (STPRTrayPsh_PRT & 0x0F) | 0x90;_delay_ms(period);
		STPRTrayPsh_PRT = (STPRTrayPsh_PRT & 0x0F) | 0xC0;_delay_ms(period);
		STPRTrayPsh_PRT = (STPRTrayPsh_PRT & 0x0F) | 0x60;_delay_ms(period);
		STPRTrayPsh_PRT = (STPRTrayPsh_PRT & 0x0F) | 0x30;_delay_ms(period);
	}
	STPRTrayPsh_PRT = (STPRTrayPsh_PRT & 0x0F) | 0x90; /* Last step to initial position */_delay_ms(period);
}

/*Pull Action*/
void stprTrayPsh_aclk(int cycles){
	
	const unsigned int period= 6;
	for(int i=0;i<cycles;i++)
	{	STPRTrayPsh_PRT = (STPRTrayPsh_PRT & 0x0F) | 0x30;_delay_ms(period);
		STPRTrayPsh_PRT = (STPRTrayPsh_PRT & 0x0F) | 0x60;_delay_ms(period);
		STPRTrayPsh_PRT = (STPRTrayPsh_PRT & 0x0F) | 0xC0;_delay_ms(period);
		STPRTrayPsh_PRT = (STPRTrayPsh_PRT & 0x0F) | 0x90;_delay_ms(period);
	}
	STPRTrayPsh_PRT = (STPRTrayPsh_PRT & 0x0F) | 0x90; /* Last step to initial position */_delay_ms(period);
}

/*Lowering Action*/
void stprMix_clk(int cycles){
	
	const unsigned int period= 6;
	for(int i=0;i<cycles;i++)
	{
		STPRMix_PRT = (STPRMix_PRT & 0x0F) | 0x90;_delay_ms(period);
		STPRMix_PRT = (STPRMix_PRT & 0x0F) | 0xC0;_delay_ms(period);
		STPRMix_PRT = (STPRMix_PRT & 0x0F) | 0x60;_delay_ms(period);
		STPRMix_PRT = (STPRMix_PRT & 0x0F) | 0x30;_delay_ms(period);
	}
	STPRMix_PRT = (STPRMix_PRT & 0x0F) | 0x90; /* Last step to initial position */_delay_ms(period);
}

/*Lifting Action*/
void stprMix_aclk(int cycles){
	
	const unsigned int period= 6;
	for(int i=0;i<cycles;i++)
	{	STPRMix_PRT = (STPRMix_PRT & 0x0F) | 0x30;_delay_ms(period);
		STPRMix_PRT = (STPRMix_PRT & 0x0F) | 0x60;_delay_ms(period);
		STPRMix_PRT = (STPRMix_PRT & 0x0F) | 0xC0;_delay_ms(period);
		STPRMix_PRT = (STPRMix_PRT & 0x0F) | 0x90;_delay_ms(period);
	}
	STPRMix_PRT = (STPRMix_PRT & 0x0F) | 0x90; /* Last step to initial position */_delay_ms(period);
}