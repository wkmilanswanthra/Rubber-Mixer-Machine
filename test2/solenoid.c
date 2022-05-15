/*
 * solenoid.c
 *
 * Created: 4/16/2021 8:05:50 AM
 *  
 */ 
#include "solenoid.h"

#define solenoid_port PD7  //select port for solenoid valve



void init_solenoid_ports()
{
	DDRD |= (1<<solenoid_port); //define  output.
}

void operate_solenoid(float pH)
{
	if (pH>pHMax ||  pH<pHMIn)
		PORTD |= (1<<solenoid_port);  //open valve
	else
	    PORTD &= ~(1<<solenoid_port);  //close valve
}