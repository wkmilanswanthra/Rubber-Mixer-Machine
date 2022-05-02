
#ifndef F_CPU
#define F_CPU 8000000UL /* Define CPU Frequency e.g. here its 8MHz */
#endif
 					
#include <avr/io.h>						/* Include AVR std. library file */
#include <util/delay.h>					/* Include inbuilt defined Delay header file */
#include "lcd.h"
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include "adc.h"

 


 
int main()
{	
	float calibration_value = 21.34;
	
	unsigned long int avgval;
	int buffer_arr[10],temp;
	char Ph[20];
	

	ADC_Init();
	LCD_Init();							/* Initialize LCD */
	while (1)
	{
		for (int l=0;l<3;l++)      //go through sensor 1,2,3
		{
			
			
				
			
			for(int i=0;i<10;i++)
			{
				buffer_arr[i]=ADC_Read(l);
				_delay_ms(30);
			}
			for(int i=0;i<9;i++)
			{
				for(int j=i+1;j<10;j++)
				{
					if(buffer_arr[i]>buffer_arr[j])
					{
						temp=buffer_arr[i];
						buffer_arr[i]=buffer_arr[j];
						buffer_arr[j]=temp;
					}
				}
			}
			avgval=0;
			for(int i=2;i<8;i++)
			avgval+=buffer_arr[i];
			float volt=(float)avgval*5.0/1024/6;
			float ph_act = -5.70 * volt + calibration_value;                
			 LCD_Clear();
			 if(l==0){
				 LCD_String("Latex");		/* write string on 1st line of LCD*/
			 }else if(l==2){
				 LCD_String("Water");
			 }else{
				 LCD_String("Acid");
			 }
			
			LCD_Command(0xc0);					/* Go to 2nd line*/
			dtostrf(ph_act,8,5,Ph);	/* Integer to string conversion */
			LCD_String(Ph);
			
			_delay_ms(500);
		}
		
		
		
	}
	
	return 0;
}
 
