/*
 * ultrahead.h
 *
 * Created: 5/10/2022 3:03:46 PM
 *  Author: Nishshanka
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define US_PORT PORTB
#define	US_PIN	PINB
#define US_DDR 	DDRB

#define US_TRIG_POS PB1
#define US_ECHO_POS  PB2

#define US_ERROR  -1
#define	US_NO_OBSTACLE	-2



void HCSR04Init();
void HCSR04Trigger();
uint16_t depth(uint16_t r);
uint16_t ultrasonic1();
uint16_t ultrasonic2();
uint16_t ultrasonic3();

//void lcd_command( unsigned char );

void HCSR04Init()
{
	
	
	US_DDR|=(1<<US_TRIG_POS);
	
}

void HCSR04Trigger()
{
	
	US_PORT|=(1<<US_TRIG_POS);	//high
	
	_delay_us(15);				//wait 15uS
	
	US_PORT&=~(1<<US_TRIG_POS);	//low

	
}

uint16_t GetPulseWidth()
{
	
	
	uint32_t i,result;

	
	for(i=0;i<600000;i++)
	{
		if(!(US_PIN & (1<<US_ECHO_POS)))
		continue;	//Line is still low, so wait
		else
		break;		//High edge detected, so break.
	}

	if(i==600000)
	return US_ERROR;	//Indicates time out
	
	//High Edge Found
	
	
	//Setup Timer1
	TCCR1A=0X00;
	TCCR1B=(1<<CS11);	
	TCNT1=0x00;			// This line start the counter to start counting time

	// Section -3 : This section checks weather the there is any object or not
	for(i=0;i<600000;i++)                // the 600000 value is used randomly to denote a very small amount of time, almost 40 miliseconds
	{
		if(US_PIN & (1<<US_ECHO_POS))
		{
			if(TCNT1 > 60000) break; else continue;   // if the TCNT1 value gets higher than 60000 it means there is not object in the range of the sensor
		}
		else
		break;
	}

	if(i==600000)
	return US_NO_OBSTACLE;	//Indicates time out

	//Falling edge found

	result=TCNT1;          // microcontroller stores the the value of the counted pulse time in the TCNT1 register. So, we're returning this value to the
	// main function for utilizing it later

	//Stop Timer
	TCCR1B=0x00;

	if(result > 60000)
	return US_NO_OBSTACLE;	//No obstacle
	else
	return (result>>1);
}

uint16_t depth(uint16_t r)
{
	int distance;

	distance=(r*0.034/2.0);
	if(distance>50)
	{
		return 0;
		
	}
	else
	{
		return 1;
	}
}

uint16_t ultrasonic1()
{
	uint16_t r;
	PORTB&=~(1<<PB3);
	PORTB&=~(1<<PB4);
	HCSR04Trigger(); // calling the ultrasonic sound wave generator function
	//Measure the width of pulse
	r=GetPulseWidth();
	return depth(r);
}

uint16_t ultrasonic2()
{
	uint16_t r;
	PORTB&=~(1<<PB3);
	PORTB|=(1<<PB4);
	HCSR04Trigger(); // calling the ultrasonic sound wave generator function
	//Measure the width of pulse
	r=GetPulseWidth();
	return depth(r);
}


uint16_t ultrasonic3()
{
	uint16_t r;
	PORTB|=(1<<PB3);
	PORTB|=(1<<PB4);
	HCSR04Trigger(); // calling the ultrasonic sound wave generator function
	//Measure the width of pulse
	r=GetPulseWidth();
	return depth(r);
}


