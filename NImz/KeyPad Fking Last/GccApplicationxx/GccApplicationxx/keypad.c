/*
 * keypad.c
 *
 * Created: 9/16/2016 5:09:58 PM
 *  Author: Nimash eshan
 */ 
 #include "keypad.h"

 void keypad_init(void)
 {
 //setting ROWs as outputs
	ROW0_DDR |=(1U<<ROW0);  
	ROW1_DDR |=(1U<<ROW1);
	ROW2_DDR |=(1U<<ROW2);
	ROW3_DDR |=(1U<<ROW3);
//setting pins as input
	LINE0_DDR&=~(1U<<LINE0);
	LINE1_DDR&=~(1U<<LINE1);
	LINE2_DDR&=~(1U<<LINE2);
	LINE3_DDR&=~(1U<<LINE3);
//enabling lines pull up
	LINE0_PULLUP|=(1U<<LINE0);
	LINE1_PULLUP|=(1U<<LINE1);
	LINE2_PULLUP|=(1U<<LINE2);
	LINE3_PULLUP|=(1U<<LINE3);
 }
 uint8_t keypad_scan(void)
 {
 uint8_t row,key,shift;
 //loop on rows
	 for(row=0;row<4;row++)
	 {
	 //put 1's on all rows
	 ROW0_PORT|=(1U<<ROW0);
	 ROW1_PORT|=(1U<<ROW1);
	 ROW2_PORT|=(1U<<ROW2);
	 ROW3_PORT|=(1U<<ROW3);
	 //put zero on the selected row
		 if(row==0)
		 {
			ROW0_PORT&=~(1U<<ROW0);
		 }
		 else if(row==1)
		 {
			ROW1_PORT&=~(1U<<ROW1);
		 }
		 else if(row==2)
		 {
			 ROW2_PORT&=~(1U<<ROW2);
		 }
		 else 
		 {
			ROW3_PORT&=~(1U<<ROW3);	 
		 }
	 //take snapshot from the input
	 shift  = (LINE0_PIN&(1U<<LINE0))>>LINE0;
	 key  = (shift<<0);
	 shift  = (LINE1_PIN&(1U<<LINE1))>>LINE1;
	 key  |= (shift<<1);
	 shift  = (LINE2_PIN&(1U<<LINE2))>>LINE2;
	 key  |= (shift<<2);
	 shift  = (LINE3_PIN&(1U<<LINE3))>>LINE3;
	 key  |= (shift<<3);
	 key=key<<4; //0x0000xxxx
	 //if there is input
	 //0xF0&LINE0|LINE1|LINE2|LINE3
	 //PIND&0x0f !=0x0f
		
		if(ALL_LINES != 1)
		{
		//delay for the input to be cleared
		while(ALL_LINES != 1);
		break;
		}
 
	 }
 //when break switch rows
	switch(row)
	{
		case 0:
		//inside the row switching switch the key
		switch(key)
		{
			case 0x70: return 'E';
			case 0xB0: return '9';
			case 0xD0: return '8';
			case 0xE0: return '7';
		}
		break;
		case 1:
		//inside the row switching switch the key
		switch(key)
		{
			case 0x70: return 'A';
			case 0xB0: return '6';
			case 0xD0: return '5';
			case 0xE0: return '4';
		}
		break;
		case 2:
		//inside the row switching switch the key
		switch(key)
		{
			case 0x70: return 'B';
			case 0xB0: return '3';
			case 0xD0: return '2';
			case 0xE0: return '1';
			
		}
		break;
		case 3:
		//inside the row switching switch the key
		switch(key)
		{
			case 0x70: return '+';
			case 0xB0: return '=';
			case 0xD0: return '0';
			case 0xE0: return 'C';
		}
		break;
	}
	//return the value
	return 0;
  }
