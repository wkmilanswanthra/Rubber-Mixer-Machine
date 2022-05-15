/*
* main.c
*
* Created: 11/20/2021 11:23:38 p. m.
* Author : Group 30
*/

//Libraries used in the Project
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <util/delay.h>

#include "i2c.h"
#include "LCD_I2C.h"
#include "keypad.h"



int num_trays = 0;
float vol = 0;



void wlcm_msg();

int num_tray();
int tray_vol();

//Display a welcome message on the display
void wlcm_msg()
{
	i2c_init();
	i2c_start();
	i2c_write(0x70);
	lcd_init();
	
	lcd_cmd(0x80);
	lcd_msg("Rubber Solution Mixer 1.0");
	lcd_cmd(0xC0);
	lcd_cmd(0x14);
	lcd_cmd(0x14);
	lcd_cmd(0x14);
	lcd_cmd(0x14);
	lcd_msg("Welcome");
	_delay_ms(500);
	for (int i= 0; i<27; i++)
	{
		lcd_cmd(0x18);
		_delay_ms(100);
	}
}



//Get the user input for the number of trays
int num_tray()
{
	
	
	redo_trays:
	
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_msg("Number of Trays?");
	lcd_cmd(0xC0);
	lcd_cmd(0x0F);
	
	char temp[10];
	char str[10];
	int digs = 0;
	
	do
	{
		strcpy(temp,keyfind());
		if (strcmp(temp,"=")==0)
		{
			if (digs>=1)
			{
				lcd_cmd(0x10);
				lcd_msg(" ");
				lcd_cmd(0x10);
				lcd_cmd(0x10);
				lcd_cmd(0x14);
				digs--;
				strcpy(&str[digs], " ");
			}
			continue;
		}
		lcd_msg(temp);
		strcpy(&str[digs],temp);
		digs++;
	} while ((strcmp(temp," ")!=0)|(atoi(str)==0));
	
	num_trays= atoi(str);
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	
	if (num_trays>=20)
	{
		lcd_msg("Enter a value less than 20");
		_delay_ms(500);
		for (int i = 0; i<27 ;i++)
		{
			lcd_cmd(0x18);
			_delay_ms(100);
		}
		goto redo_trays;
	}
	return num_trays;
}

//Getting the volume of trays in milliliters
int tray_vol()
{

	redo_vol:
	
	
	lcd_msg("Vol.of a Tray(ml)");
	lcd_cmd(0xC0);
	lcd_cmd(0x0F);
	
	char temp[10];
	char str[10];
	int digs = 0;
	
	do
	{
		strcpy(temp,keyfind());
		
		if (strcmp(temp,"=")==0)
		{
			if (digs>=1)
			{
				lcd_cmd(0x10);
				lcd_msg(" ");
				lcd_cmd(0x10);
				lcd_cmd(0x10);
				lcd_cmd(0x14);
				digs--;
				strcpy(&str[digs]," ");
			}
			continue;
		}
		lcd_msg(temp);
		strcpy(&str[digs],temp);
		digs++;
	} while ((strcmp(temp," ")!=0)|(atoi(str)==0));
	
	vol= atoi(str);
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	
	if (vol>=5000)
	{
		lcd_msg("Enter a value less than 5000");
		_delay_ms(500);
		for (int i = 0; i<28 ; i++)
		{
			lcd_cmd(0x18);
			_delay_ms(100);
		}
		goto redo_vol;
	}
	return vol;
	
}

void disp_w_low()
{
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_msg("Water Level Low!");
}
void disp_a_low()
{
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_msg("Acid Level Low!");
}
void disp_l_low()
{
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_msg("Latex Level Low!");
}