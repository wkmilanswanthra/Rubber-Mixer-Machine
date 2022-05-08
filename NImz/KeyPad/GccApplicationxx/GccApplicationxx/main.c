/*
 * test5.c
 *
 * Created: 9/16/2016 5:08:21 PM
 * Author : Ramy Elfouly
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include "keypad.h"
#include "lcd.h"
#include <util/delay.h>

int main(void)
{
	uint8_t data_from_keypad;
    keypad_init();
	lcd_init();
	lcd_write_string("Hello!");
	_delay_ms(1000);
	lcd_clearDisplay();
    while (1) 
    {
	data_from_keypad = keypad_scan();
	if(data_from_keypad != 0)
	{
	lcd_write_character(data_from_keypad);
	}
	
    }
}

