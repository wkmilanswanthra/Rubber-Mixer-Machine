#include "flowsensor.h"

float calibrationFactor = 4.5;
float flowRate=0;
volatile unsigned int pulseCount1=0;
volatile unsigned int pulseCount2=0;
volatile unsigned int pulseCount3=0;
unsigned long oldTime=0;
unsigned int flowMilliLitres=0;
unsigned long totalMilliLitres=0;
volatile unsigned long int millisec=0;
volatile unsigned long int sec=0;
int v_water ;
int v_latex ;
int v_acid ;


void timer_1(){

	TCCR1A =(0 << WGM11)| (0 << WGM10 );// CTC
	TIMSK |= (1 << OCIE1A);//Set interrupt on compare match
	TCCR1B |= (1 << CS12) | (1 << CS10);// set pre scaler to 1024 and start the timer
	OCR1A = 0x07;
}

void pump_w(){
	
	PORTB = PORTB | (1<<5);    /* Turn on the Relay and motor ON*/
	timer_1();
	DDRD &= ~(1 << DDD2);     /*Clear the PD2 pin*/
	PORTD =	 0xFF;             /* turn On the Pull-up */
	DDRD &= ~(1<<PD2);        /* Make INT0 pin as Input */
	GICR = (1<<INT0);         /* Enable INT0*/
	MCUCR = ((1<<ISC00)|(1<<ISC01));/* Trigger INT0 on Rising Edge triggered */
	
	sei();                   /*enable interrupts*/
	while (totalMilliLitres!=v_water)   {
		if((millisec-oldTime)>=1000)
		{
			sec++;
			if(sec==1)
			{
				cli();
				
				flowRate = ((1000.0 / (millisec - oldTime)) * pulseCount1) / calibrationFactor;
				oldTime = millisec;
				flowMilliLitres = (flowRate / 60) * 1000;
				totalMilliLitres += flowMilliLitres;
				
				millisec=0;
				sec=0;
				pulseCount1 = 0;

				sei();
			}
		}
	}
	PORTB = PORTB & (~(1<<5)); /*Turn off the relay*/
	
}
ISR (TIMER1_COMPA_vect){
	millisec++;
}
ISR (INT0_vect){
	pulseCount1++;
}

void pump_l(){
	PORTB = PORTB | (1<<6); /* Turn on the Relay and motor ON*/
	timer_1();
	DDRD &= ~(1 << DDD2);     // Clear the PD2 pin
	PORTD = 0xFF;   // turn On the Pull-up
	DDRD &= ~(1<<PD3);		/* Make INT1 pin as Input */
	GICR = (1<<INT1);		/* Enable INT1*/
	MCUCR = ((1<<ISC10)|(1<<ISC11));/* Trigger INT1 on Rising Edge triggered */

	sei();// enable interrupts
	
	while (totalMilliLitres!=v_latex)   {
		if((millisec-oldTime)>=1000)
		{
			sec++;
			if(sec==1)
			{
				cli();
				
				flowRate = ((1000.0 / (millisec - oldTime)) * pulseCount2) / calibrationFactor;
				oldTime = millisec;
				flowMilliLitres = (flowRate / 60) * 1000;
				totalMilliLitres += flowMilliLitres;

				millisec=0;
				sec=0;
				pulseCount2 = 0;

				sei();
			}
		}
	}
	PORTB = PORTB & (~(1<<6)); /*Turn off the relay*/
	
}


ISR (INT1_vect){
	pulseCount2++;
}

void pump_a(){
	PORTB = PORTB | (0<<4);
	PORTB = PORTB | (0<<3);    /*multiplexer input*/
	PORTB = PORTB | (1<<7); /* Turn OFF the Relay and motor ON*/
	timer_1();
	DDRB &= ~(1 << DDB2);     // Clear the PD2 pin
	PORTB = 0xFF;   // turn On the Pull-up
	DDRB &= ~(1<<PB2);		/* Make INT2 pin as Input */
	GICR = (1<<INT2);		/* Enable INT2*/
	MCUCR = (1<<ISC2);/* Trigger INT2 on Rising Edge triggered */


	sei();// enable interrupts
	
	while (totalMilliLitres!=v_acid)   {
		if((millisec-oldTime)>=1000)
		{
			sec++;
			if(sec==1)
			{
				cli();
				
				flowRate = ((1000.0 / (millisec - oldTime)) * pulseCount3) / calibrationFactor;
				oldTime = millisec;
				flowMilliLitres = (flowRate / 60) * 1000;
				totalMilliLitres += flowMilliLitres;
				
				millisec=0;
				sec=0;
				pulseCount3 = 0;

				sei();
				
			}
		}
	}
	PORTB = PORTB & (~(1<<7)); /*Turn off the relay*/
	
}


/*ISR (INT2_vect){
	pulseCount3++;
}*/


//--------------------------------------------------Nishshanka's Code--------------------------------------
static volatile unsigned int tCount = 0;
static volatile int i = 0;
double distance = 0;


void initUS(){
	
	DDRB = DDRB | 1 << DDB1;
	//DDRD = DDRD & ~(1 << DDD2) ;
	//PORTD = PORTD & ~(1 << PD2);
	DDRB = DDRB & ~(1 << DDB2) ;
	PORTB = PORTB & ~(1 << PB2);
	DDRB= DDRB | 1 << DDB3;
	DDRB= DDRB | 1 << DDB4;
	_delay_ms(50);
	MCUCSR |= 1 << ISC2;
	GIFR &= ~(1<< INTF2);
	GICR |= 1<<INT2;
	//MCUCR |= 1<<ISC00;
	TIMSK |= 1 << TOIE1;
	sei();
}

uint8_t ultrasonic1()
{
	v_water=12;
	PORTB=PORTB & ~(1 << PB3);
	PORTB=PORTB & ~(1 << PB4);
	trigPulse();
	distance = tCount*1000000.0/F_CPU/58;
	v_water=13;
	return retDistance(distance);

}


uint8_t ultrasonic2()
{
	PORTB=PORTB | 1 << PB3;
	PORTB=PORTB & ~(1 << PB4);
	trigPulse();
	distance = tCount*1000000.0/F_CPU/58;
	return retDistance(distance);

}

uint8_t ultrasonic3()
{
	PORTB=PORTB & ~(1 << PB3);
	PORTB=PORTB | 1 << PB4;
	trigPulse();
	distance = tCount*1000000.0/F_CPU/58;
	return retDistance(distance);

}


void trigPulse()
{
	PORTB = PORTB | 1<<PB1;
	_delay_us(15);
	PORTB = PORTB & ~(1<<PB1);
	_delay_us(15);
	
}

uint8_t retDistance(double distance)
{
	v_acid =15;
	if (distance >50)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	_delay_ms(200);
	
}

ISR(TIMER1_OVF_vect){
	TCCR1B = 0;
	tCount = 200;
	TCNT1 = 0;
	i = 0;
}

ISR(INT2_vect)
{
	GICR &= ~(1<<INT2);
	MCUCSR ^= 1 << ISC2;
	GIFR &= ~(1<< INTF2);
	GICR |= 1<<INT2;
	pulseCount3++;

	if(i == 0)
	{
		TCCR1B |= 1<<CS10;
		i = 1;
	}
	else
	{
		TCCR1B = 0;
		tCount = TCNT1;
		TCNT1 = 0;
		i = 0;
	}
}