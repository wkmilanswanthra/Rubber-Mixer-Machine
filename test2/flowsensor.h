/*
 * flowsensor.h
 *
 * Created: 4/30/2022 8:05:26 PM
 *  Author: Ishanka
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>

void pump_w();
void pump_l();
void pump_a();
void timer_1();

float calibrationFactor = 4.5;
float flowRate=0;
volatile unsigned int pulseCount=0;
unsigned long oldTime=0;
unsigned int flowMilliLitres=0;
unsigned long totalMilliLitres=0;
volatile unsigned long int millisec=0;
volatile unsigned long int sec=0;
//int v_water=5000;

void timer_1(){

	TCCR1A = (0 << WGM11)| (0 << WGM10 );
	TCCR1B = (0 << WGM12)| (0 << WGM13 );// normal mode
	TCCR1B |= (1 << CS12) | (1 << CS10);// set pre scaler to 1024 and start the timer
	TCNT1=0;
}

void pump_w(){
	DDRB |=(1<<5);
	PORTB &=~(1<<5);
	
	PORTB = PORTB | (0<<4);
	PORTB = PORTB | (0<<3);    /*multiplexer input*/
	PORTB = PORTB | (1<<5);    /* Turn on the Relay and motor ON*/
	timer_1();
	DDRD &= ~(1 << DDD2);     /*Clear the PD2 pin*/
	PORTD = 0xFF;             /* turn On the Pull-up */
	DDRD &= ~(1<<PD2);        /* Make INT0 pin as Input */
	GICR = (1<<INT0);         /* Enable INT0*/
	MCUCR = ((1<<ISC00)|(1<<ISC01));/* Trigger INT0 on Rising Edge triggered */
	
	sei();                   /*enable interrupts*/
	while (totalMilliLitres!=1000)   {
		if((millisec-oldTime)>=1000)
		{
			sec++;
			if(sec==1)
			{
				cli();
				
				flowRate = ((1000.0 / (millisec - oldTime)) * pulseCount) / calibrationFactor;
				oldTime = millisec;
				flowMilliLitres = (flowRate / 60) * 1000;
				totalMilliLitres += flowMilliLitres;
			}
		}
	}
	PORTB = PORTB & (~(1<<5)); /*Turn off the relay*/
	millisec=0;
	sec=0;
	pulseCount = 0;
	
	sei();
}
ISR (TIMER1_COMPA_vect){
	millisec++;
}
ISR (INT0_vect){
	pulseCount++;
}

void pump_l(){
	DDRB |=(1<<6);
	PORTB &=~(1<<6);
	PORTB = PORTB | (1<<6); /* Turn on the Relay and motor ON*/
	timer_1();
	DDRD &= ~(1 << DDD2);     // Clear the PD2 pin
	PORTD = 0xFF;   // turn On the Pull-up
	DDRD &= ~(1<<PD3);		/* Make INT1 pin as Input */
	GICR = (1<<INT1);		/* Enable INT0*/
	MCUCR = ((1<<ISC10)|(1<<ISC11));/* Trigger INT1 on Rising Edge triggered */

	sei();// enable interrupts
	
	while (totalMilliLitres!=1000)   {
		if((millisec-oldTime)>=1000)
		{
			sec++;
			if(sec==1)
			{
				cli();
				
				flowRate = ((1000.0 / (millisec - oldTime)) * pulseCount) / calibrationFactor;
				oldTime = millisec;
				flowMilliLitres = (flowRate / 60) * 1000;
				totalMilliLitres += flowMilliLitres;

				
			}
		}
	}
	PORTB = PORTB & (~(1<<6)); /*Turn off the relay*/
	millisec=0;
	sec=0;
	pulseCount = 0;
	
	sei();
}


ISR (INT1_vect){
	pulseCount++;
}

void pump_a(){
	DDRB |=(1<<7);
	PORTB &=~(1<<7);
	PORTB = PORTB | (1<<7); /* Turn OFF the Relay and motor ON*/
	timer_1();
	DDRB &= ~(1 << DDB2);     // Clear the PD2 pin
	PORTB = 0xFF;   // turn On the Pull-up
	DDRB &= ~(1<<PB2);		/* Make INT2 pin as Input */
	GICR = (1<<INT2);		/* Enable INT0*/
	MCUCR = (1<<ISC2);/* Trigger INT2 on Rising Edge triggered */


	sei();// enable interrupts
	
	while (totalMilliLitres!=1000)   {
		if((millisec-oldTime)>=1000)
		{
			sec++;
			if(sec==1)
			{
				cli();
				
				flowRate = ((1000.0 / (millisec - oldTime)) * pulseCount) / calibrationFactor;
				oldTime = millisec;
				flowMilliLitres = (flowRate / 60) * 1000;
				totalMilliLitres += flowMilliLitres;

				
			}
		}
	}
	PORTB = PORTB & (~(1<<7)); /*Turn off the relay*/
	millisec=0;
	sec=0;
	pulseCount = 0;
	
	sei();
}


ISR (INT2_vect){
	pulseCount++;
}