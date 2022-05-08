/*
 * calculator.c
 *
 * Created: 9/22/2016 7:35:52 PM
 *  Author: WALY
 */
#include "calculator.h"
#include <stdint.h>
#include <string.h>
/*extern uint8 Flag; */
sint64 Result=0;
sint64 Operands[MaxNumberOfOperands];
uint8 Operations[MaxNumberOfOperations];
sint8 Digits[MaxNumberOfDigits];

uint8 OperandsCounter=0; /*How many operands entered*/
uint8 OperationsCounter=0; /*how many operations*/
uint8 DigitsCounter=0;/*how many digits is entered including math symbols*/

unsigned char FirstNumberSign=false; /*if Digits[0]=negative value means that operand[0] is negative*/
unsigned char SignNumberFlagToConvertInt64=false;
unsigned char OtherNumberSign=false;

uint8 getdata()
{
	
	uint8 temp=0;/*To get into the loop for the first time and hold the value of the key pressed*/
	temp=keypad_scan();
	while (temp != '=')
	{
		if(temp != 0)
		{
			Digits[DigitsCounter]=temp; /*storing any thing the user input*/
			lcd_write_character(Digits[DigitsCounter]);
			DigitsCounter++;
			_delay_ms(300);	/*delay time between each press */
		}
		temp=keypad_scan();
	}

	Digits[DigitsCounter]='=';
	lcd_write_character(Digits[DigitsCounter]);	
	DigitsCounter++;
	return AnalyzePoint;
}

uint32 powerten(uint8 x)
{
	uint32 m=1,index=0;
	for(index=1;index<=x;index++)
	m*=10;
	return m;
}
uint64 ConvertToInt(sint8 * ptr,uint8 len)
{
	uint8 index;
	sint64 value=0;
		
	for(index=0;index<len;index++)
	{
		value+=(ptr[len-index-1]-48)*powerten(index);	
	}
	
	if(SignNumberFlagToConvertInt64)
	{
		
		value= -value; 
		SignNumberFlagToConvertInt64=false;
	}
	 
	return value;
}

uint8 analyze()
{	
	sint8 TempArr[MaxNumberOfDigits]={0};
	uint8 TempIndex=0;
	uint8 index=0;
	
	if (IsOperation(Digits[0]) && Digits[0]!= '-') //input is *5
	{	
		lcd_clearDisplay();
		lcd_write_string("MATH ERROR");
		_delay_ms(1000);
		return Reset;
	}
	
	
	if(Digits[0]== '-' && IsOperation(Digits[1])) //check if first number is signed
	{
		FirstNumberSign =true; /*To register the number in TempArr without conflict with the second condition*/
		SignNumberFlagToConvertInt64=true; /*To make a note that the number which ConvertInt64 will convert is negative*/
		index++; /*TempArr[0]= Digits[1]*/
		
	}
	
	while(DigitsCounter != 0) //incremented in getdata
		{
			/*search for operation one it find it convert whats before it to a single integer and start search for second number*/
			
			if(((Digits[index]>='0') && (Digits[index]<='9')) || FirstNumberSign||OtherNumberSign) 
			{
				TempArr[TempIndex]=Digits[index];
				TempIndex++;
				FirstNumberSign =false;
				OtherNumberSign =false;
			}
							
			else if (((IsOperation(Digits[index]))||(Digits[index]== '=')))
			{
				Operations[OperationsCounter]=Digits[index];
				OperationsCounter++;
				Operands[OperandsCounter]=ConvertToInt(TempArr,TempIndex);
				OperandsCounter++;
				TempIndex=0;
					if(Digits[index+1] == '-' && index >0) /*If the 2nd operand is signed */
					{
						OtherNumberSign=true;
						SignNumberFlagToConvertInt64=true;
						index++;
					}
					else if(IsOperation(Digits[index+1])) /*if two symbols after each other ++ or *% */
					{
						lcd_clearDisplay();
						lcd_write_string("MATH ERROR");
						_delay_ms(1000);
						return Reset;
						
					}
					
			}
			index++;
			DigitsCounter--;
		}
		
			return CalculatePoint;	
			
}


uint8 calculate()
{
	uint8 priority=false;
	
	if(OperationsCounter>2)	/* > 2 As equal sign included*/
	{									
		if(Operations[1] != Operations[0]) priority=true;		
	}		
	
	if(OperandsCounter == 1)
	{	
		Result=Operands[0];
		return DisplayPoint;	
	}

if(priority==false){	
	if((OperandsCounter>1))
	{
		uint8 index=0;
		switch(Operations[0])
		{
			case '+':{
						Result=Operands[0];
						for(index=1;index<OperandsCounter;index++)
							Result+=Operands[index];				
						break;
					 }
					
			case '*':{
						Result=1;
						for(index=0;index<OperandsCounter;index++)
							Result*=Operands[index];
						break;
					 }
					
			case '-':{
						Result=Operands[0];
						for(index=1;index<OperandsCounter;index++)
							Result-=Operands[index];
						break;
					 }
						
			case '%':{
						Result=Operands[0]; 
						for(index=1;index<OperandsCounter;index++)
							Result/=Operands[index];
						break;
					 }
					
			default:{
						lcd_clearDisplay();
						lcd_write_string("MATH ERROR");
						_delay_ms(1000);
						return Reset;
						break;
					}					
		}
		
		return DisplayPoint;
		
	}
		}	
else
	{	
	if((OperandsCounter>1))
	{
		
		uint8 code=0;
		if(Operations[0]=='*' && Operations[1] == '+') code=1;
		else if(Operations[0]=='+' && Operations[1] == '*') code=2;
		else if(Operations[0]=='+' && Operations[1] == '-') code=3;
		else if(Operations[0]=='-' && Operations[1] == '+') code=4;
		else if(Operations[0]=='*' && Operations[1] == '%') code=5;
		else if(Operations[0]=='%' && Operations[1] == '*') code=6;
		else if(Operations[0]=='%' && Operations[1] == '+') code=7;
		else if(Operations[0]=='+' && Operations[1] == '%') code=8;
		else if(Operations[0]=='*' && Operations[1] == '-') code=9;
		else if(Operations[0]=='-' && Operations[1] == '*') code=10;
		else if(Operations[0]=='%' && Operations[1] == '-') code=11;
		else if(Operations[0]=='-' && Operations[1] == '%') code=12;
		else code =0; 
		
		switch(code){
			case 1: Result=(Operands[0]*Operands[1])+Operands[2]; break;
			case 2: Result=Operands[0]+(Operands[1]*Operands[2]); break;
			case 3: Result=Operands[0]+(Operands[1]-Operands[2]); break;
			case 4: Result=(Operands[0]-Operands[1])+Operands[2]; break;
			case 5: Result=Operands[0]*(Operands[1]/Operands[2]); break;
			case 6: Result=(Operands[0]/Operands[1])*Operands[2]; break;
			case 7: Result=Operands[0]/Operands[1]+Operands[2]; break;
			case 8: Result=Operands[0]/Operands[1]+Operands[2]; break;
			case 9: Result= Operands[0]*Operands[1]-Operands[2]; break;
			case 10: Result=Operands[0]-Operands[1]*Operands[2]; break;
			case 11: Result= Operands[0]/Operands[1]-Operands[2];break;
			case 12: Result= Operands[0]-Operands[1]/Operands[2];break;
					
			default:
				{
					lcd_write_string("PRIORITY ERROR");
					_delay_ms(1000);	
					return Reset;
					break;
				}
		}	
		return DisplayPoint;
		
	}
		}
		
	return DisplayPoint;
}
		

uint8 display()
{	unsigned char str[16];
	sint64 sum = Result;
	uint8 i = 0;
	uint8 digit;
	uint8 Negative=0;
	
	if(sum < 0){
		sum=-sum;
		Negative=1;
	}
	
	do
	{
		digit = sum % 10;
		if (digit < 0xA)
		str[i++] = '0' + digit;
		else
		str[i++] = 'A' + digit - 0xA;
		sum /= 10;
	}
	while (sum > 0);

	if(Negative) str[i]='-';
	i++;
	str[i] = '\0';
	strrev(str);
	Negative=0;
	
	lcd_gotoxy (1,1);
	lcd_write_string(str);
	_delay_ms(1000);
	
	return Reset;
}


uint8  Resetall()
{
	uint8 index=0;
	for(index=0;index<MaxNumberOfDigits;index++)
	Digits[index]=0;
	for(index=0;index<MaxNumberOfOperands;index++)
	Operands[index]=0;
	for(index=0;index<MaxNumberOfOperations;index++)
	Operations[index]=0;
	OperandsCounter=0;
	OperationsCounter=0;
	DigitsCounter=0;
	Result=0;
	while(keypad_scan()==0){}
	lcd_clearDisplay();
	return StartPoint;
}




// uint8 display()
// {
// 	char str[16];
// 	unsigned short i= 0;
// 	unsigned short j =0;
// 	char reverse[16];
// 	if(Result!=0)
// 	{
// 		while(Result != 0)
// 		{
//
// 			reverse[i] = (Result%10)+48;
// 			Result=Result/10;
// 			i++;
//
// 		}
//
// 		i--;
//
// 		while(i>0)
// 		{
//
// 			str[j] = reverse[i];
//
// 			i--;
// 			j++;
//
// 		}
// 		str[j] = reverse[i];
//
// 		str[j+1]='\0';
//
// 	}
//
//
// 	else
// 	{
//
// 		str[0]='\0';
//
// 	}
//
// 	uint8 w = 0;
// 	while(str[w] != '\0')
// 	{
// 		lcd_write_character(str[w]);
// 		w++;
// 	}
// 	//lcd_write_string(str);
// 	_delay_ms(1000);
// 	return Reset;
// }