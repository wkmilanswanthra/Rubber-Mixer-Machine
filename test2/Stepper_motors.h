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
void acvt_mixer();
void acvt_trayPsh();
void acvt_lwr_mixr();

/* Tray Pusher */
void acvt_trayPsh(){
	stprTrayPsh_init();
	stprTrayPsh_clk(2);
	_delay_ms(10);
	stprTrayPsh_aclk(2) ;
}
/* Lowering Mixer */
void acvt_lwr_mixr(){
	stprMix_init();
	stprMix_clk(2);
	_delay_ms(10);
	//acvt_mixer();
	_delay_ms(10);
	stprMix_aclk(2);
}

//Stepper Motor functions
void stprTrayPsh_init(){
	STPRTrayPsh_DDR |= 0xFF;
	STPRTrayPsh_PRT &= 0x0F;
	
}
void stprMix_init(){
	STPRMix_DDR = 0xFF;
	STPRMix_PRT = 0X00;
	
}

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