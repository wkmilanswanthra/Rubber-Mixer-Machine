/*
 * Main code.c
 *
 * Created: 4/10/2021 5:05:08 PM
 */ 

#define F_CPU 800000UL 


#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "lcd.h"
#include "ADC.h"
#include "solenoid.h"


void start_lcd();
void display_readings(float ph);
float pH_reading();


int main(void)
{
	float ph;
	
	start_lcd(); //display on, lcd pins
	adc_init();
	init_solenoid_ports();
	
	while (1)
	{
		
		ph=pH_reading(); //ph reading
		
		display_readings(ph);
		
		operate_solenoid(ph);   //operate solenoid valve to remove water
		
	}
}

float pH_reading(){
	int adc_ph=adc_read(3);   //ph reading at PA3
	
	//float pH=2*((adc_ph*5)/1024.0)+1.2;
	
	float pH=14/1024.0*adc_ph;

	
	return pH;
}


void start_lcd()
{
	lcd_init(LCD_DISP_ON); //display on, cursor off  
	lcd_clrscr();
	lcd_gotoxy(0,0);
	_delay_ms(50); //delay for the water change
}

void display_readings(float ph)
{
	char buffer[10]; 
	
	//display ph reading
	lcd_gotoxy(0,2);
	lcd_puts("pH=");
	sprintf(buffer,"%2.2f",ph);
	lcd_putc(buffer[0]);  //character 0
	lcd_putc(buffer[1]);  //character 1
	lcd_putc(buffer[2]);  //character 2
	lcd_putc(buffer[3]);  //character 3
	free(buffer);
	//display output solenoid valve
	if (ph>pHMax ||  ph<pHMIn)
	{
		char buff[12]="solenoid_ON ";
		lcd_gotoxy(8,2);
		lcd_puts(buff);
	}
	else
	{
		char buff[12]="solenoid_OFF";
		lcd_gotoxy(8,2);
		lcd_puts(buff);
	}
	
}


