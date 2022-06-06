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

//Tray Pusher
#include "Stepper_motors.h"
//Mixer
#include "dc.h"
//pH Sensor
#include "adc.h"
//AC Motor
#include "ToRelay.h"
//Ultrasonic Sensor
//#include "ultrasonic.h"
//IR Sensor
#include "IRSensor.h"
//Flow Sensor
#include "flowsensor.h"
//Display
#include "lcd_func.h"


float pH;
int adc_ph, var1;


int main(void)
{
	//------------------------------display on-----------------------------------
	wlcm_msg(); //display the welcome message 
	int num_trays = num_tray(); // get the user input for the number of trays to be processed
	int vol = tray_vol(); //get the user input for the volume of a tray
	initUS();
	
	//Main Program Loop
	while(num_trays>0){
		//------------------------------ultrasonic-----------------------(In progress)

		while (ultrasonic1())	// Display a message if the liquid is empty
		{
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_msg("water tank empty");
		}

		
		while (ultrasonic2())	// Display a message if the liquid is empty
		{
			
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_msg("latex tank empty");
		}
		

		while (ultrasonic3())	// Display a message if the liquid is empty
		{
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_msg("acid tank empty");
		}
		
		//----------------------------------ph sensor--------------------------(in progress)
		
		adc_init();
		
		adc_ph=adc_read(3);   //ph reading at PA3
		
		pH=14/1024.0*adc_ph;  //float pH=2*((adc_ph*5)/1024.0)+1.2;
		
		
		//calculate the volume of water,latex and acid needed
		float ph0 = 8.00; // standard pH level of the final mixer
		float l1; // The acid volume liquid which we  need to find
		float l2 = vol; // Volume of the Tray
		float c1 = 0.01; // concentration of acid
		
		float antiLogPh0 = pow(10, ph0);  // antilog of the pH0
		float logPh1 = log10(pH);        // log of the pH1

		l1 = ((1000*l2 * antiLogPh0) + (l2*logPh1)) / c1;
		
		//--------------------------------conveyor start------------------------------
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_msg("Machine started");
		
		
		switchon();	//activate the relay switch to the AC motor
		
		//---------------------------------stepper push-------------------------------
	
		stprTrayPsh_init();	// initialize the stepper motors
		stprTrayPsh_clk(100);	// rotate the stepper motors to push the tray onto the conveyor
		
		//--------------------------------Ir detector---------------------------------
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
		stprTrayPsh_init();	// initialize the stepper motors
		stprTrayPsh_aclk(100);// rotate the stepper motors to pull the handle
		
		
		//----------------------------tray holder down (mixer)----------------------------
		
		stprMix_init(); //initiate the stepper motor
		stprMix_clk(100);	// rotate the stepper motor to lower the mixer
		
		//----------------------------liquid pumps {flow sensor}--------------------------
	
		pump_w(); //function of the water pump
		pump_l(); //function of the latex pump
		pump_a(l1); //function of the acid pump
		
		//---------------------------------DC motor (Mixer)-------------------------------
		
		acvt_mixer();
		
		//------------------------------tray holder up (mixer)----------------------------
		
		stprMix_init();//initiate the stepper motor
		stprMix_aclk(100);// rotate the stepper motor to lower the mixer;
		
		//------------------------------conveyor belt start-------------------------------
		
		switchon();
		
		
		num_trays--; //reduce the number of trays by 1
		
		_delay_ms(5000);
		
		
		switchoff(); //deactivate the conveyor belt
		
		_delay_ms(2000);
		
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_msg("End of cycle");
		
		_delay_ms(2000);
	}
	
}



