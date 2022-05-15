/*
 * torelay.h
 *
 * Created: 5/12/2022 5:49:20 PM
 *  Author: Nishshanka
 */


void switchon();
void switchoff();



void switchon()
{
	DDRC |=(1<<PC3);
	PORTC &=~(1<<PC3);
	
	PORTC|=(1<<PC3);
}

void switchoff()
{
	DDRC |=(1<<PC3);
	PORTC &=~(1<<PC3);
	
	PORTC&=~(1<<PC3);
}
