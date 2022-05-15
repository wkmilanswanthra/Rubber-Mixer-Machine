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

#define F_CPU 1600000UL
#define MAX 100
//-----------------------------Custom Header Files---------------------------------

//Keypad
#include "keypad.h"
//Tray Pusher
#include "Stepper_motors.h"
//Mixer
#include "dc.h"
//pH Sensor
#include "adc.h"
//AC Motor
#include "ToRelay.h"
//Ultrasonic Sensor
#include "sensor.h"
//IR Sensor
#include "IRSensor.h"
//Flow Sensor
#include "flowsensor.h"
//Display
#include "lcd_func.h"



int main(void)
{
	//------------------------------display on-----------------------------------
	wlcm_msg(); //display the welcome message 
	int num_trays = num_tray(); // get the user input for the number of trays to be processed
	int vol = tray_vol(); //get the user input for the volume of a tray
		
	//Main Program Loop
	while(num_trays>0){
		//------------------------------ultrasonic-----------------------(In progress)
		
		
		/*ultrasonic1();	//activate ultrasonic sensor in the water tank
		if (!depth())	// Display a message if the liquid is empty
		{
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_msg("liqd emt");
		}
		
		
		ultrasonic2();	//activate ultrasonic sensor in the acid tank
		if (!depth())	// Display a message if the liquid is empty
		{
		}
		
		
		ultrasonic3();	//activate ultrasonic sensor in the latex tank
		if (!depth())	// Display a message if the liquid is empty
		{
		}*/
		
		//----------------------------------ph sensor--------------------------(in progress)
		
		adc_init();
		
		int adc_ph=adc_read(0);   //ph reading at PA3
		
		float pH=14/1024.0*adc_ph; //float pH=2*((adc_ph*5)/1024.0)+1.2;
		
		int len = snprintf(NULL, 0, "%f", pH);
		char *result = malloc(len + 1);
		snprintf(result, len + 1, "%f", pH);
		
		//calculate the volume of water,latex and acid needed
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_msg(result);
		
		_delay_ms(2000);
		
		
		//--------------------------------conveyor start------------------------------
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_msg("Acvt Conveyor");
		
		
		switchon();	//activate the relay switch to the AC motor
		
		//---------------------------------stepper push-------------------------------
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_msg("Acvt tray push");
		
		stprTrayPsh_init();	// initialize the stepper motors
		stprTrayPsh_clk(100);	// rotate the stepper motors to push the tray onto the conveyor
		
		//--------------------------------Ir detector---------------------------------
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_msg("Acvt IR sensor");
		
		while(1){
			if (act_IR())		//if the IR function returns a true value the conveyor will stop
			{
				lcd_cmd(0x80);
				lcd_msg("Dactvt Conveyor");
				lcd_cmd(0xC0);
				switchoff();
				break;
			}
		}
		
		//--------------------------------stepper pull--------------------------------
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_msg("back try psh");
		
		stprTrayPsh_init();	// initialize the stepper motors
		stprTrayPsh_aclk(100);// rotate the stepper motors to pull the handle
		
		
		//----------------------------tray holder down (mixer)----------------------------
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_msg("Acvt stpr mxr");
		
		stprMix_init(); //initiate the stepper motor
		stprMix_clk(100);	// rotate the stepper motor to lower the mixer
		
		//----------------------------liquid pumps {flow sensor}--------------------------
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_msg("Acvt pumps");
		
		pump_w();
		pump_l();
		pump_a();
		
		//---------------------------------DC motor (Mixer)-------------------------------
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_msg("Acvt mixer");
		
		acvt_mixer();
		
		//------------------------------tray holder up (mixer)----------------------------
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_msg("Acvt mixer Up");
		
		stprMix_init();//initiate the stepper motor
		stprMix_aclk(2);// rotate the stepper motor to lower the mixer;
		
		//------------------------------conveyor belt start-------------------------------
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_msg("Acvt Conveyor");
		
		switchon();
		
		
		num_trays--; //reduce the number of trays by 1
		
		_delay_ms(5000
		);
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_msg("End of program");
		
		_delay_ms(2000);
	}
	
}



