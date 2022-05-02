/*
 * test5.c
 
 *
 * Created: 9/16/2016 5:08:21 PM
 * Author : WALY
 */
 
#define F_CPU 1000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "keypad.h"
#include "lcd.h"
#include "types.h"
#include "calculator.h"


int main(void)
{
    keypad_init();
	lcd_init();
	lcd_write_string("University of Moratuwa");
	_delay_ms(1500);
	lcd_clearDisplay();
	lcd_write_string("Group 30 Project");
	_delay_ms(1500);
	lcd_clearDisplay();
	lcd_write_string("Automated latex mixer");
	_delay_ms(1500);
	lcd_clearDisplay();
	lcd_write_string("Keypad and PH sensor by Nimash");
	_delay_ms(1500);
	lcd_clearDisplay();
	lcd_write_string("Enter the Number of Trays");
	_delay_ms(1500);
	lcd_clearDisplay();
	lcd_write_string("Enter the Volume of the tray");
	_delay_ms(1500);
	lcd_clearDisplay();
	
    uint8 Flag;
 
    while (1) 
    {
		Flag=StartPoint;
		while(Flag==StartPoint)		{   Flag=getdata();	  }
		while(Flag==AnalyzePoint)	{   Flag=analyze();	  }
		while(Flag==CalculatePoint)	{   Flag=calculate(); }
		while(Flag==DisplayPoint)	{   Flag=display();	  }
		while(Flag==Reset)			{   Flag=Resetall();  }
    }
}

