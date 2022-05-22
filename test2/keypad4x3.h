#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"
#include "myutils.h"

#define KEYPAD A  //KEYPAD IS ATTACHED ON PORTA

//Don't Touch the lines below
//*******************************
#define KEYPAD_PORT PORT(KEYPAD)
#define KEYPAD_DDR   DDR(KEYPAD)
#define KEYPAD_PIN   PIN(KEYPAD)


uint8_t GetKeyPressed();

 uint8_t GetKeyPressed()
{
	uint8_t r,c;
	
	KEYPAD_PORT|= 0X0F;
	
	for(c=0;c<3;c++)
	{
		KEYPAD_DDR&=~(0X7F);
		
		KEYPAD_DDR|=(0X40>>c);
		for(r=0;r<4;r++)
		{
			if(!(KEYPAD_PIN & (0X08>>r)))
			{
				return (r*3+c);
			}
		}
	 }
	 
	 return 0XFF;//Indicate No key pressed
}