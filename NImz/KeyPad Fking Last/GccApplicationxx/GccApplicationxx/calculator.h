/*
 * calculator.h
 *
 * Created: 9/22/2016 7:10:07 PM
 *  Author: WALY
 */ 

#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#define F_CPU 1000000UL //1MHz Clock frequency
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "types.h"
#include "keypad.h"
#include "math.h"

#define MaxNumberOfDigits 16
#define MaxNumberOfOperands 12	//including =
#define MaxNumberOfOperations MaxNumberOfOperands-1 //excluding =

#define IsOperation(n) ((n=='*')||(n=='+')||(n=='-')||(n=='%'))

#define Reset			0
#define StartPoint		1
#define AnalyzePoint	2
#define CalculatePoint	3
#define DisplayPoint	4


//extern uint8 Flag;
//enum Flags{Reset=0,StartPoint,AnalyzePoint,CalculatePoint,DisplayPoint,ErrorPoint};

//Function Prototypes
uint8 getdata(); //store any key pressed from user

uint8 analyze(); //differentiates between operands & operations, signed & unsigned 
uint32 powerten(uint8 x);
uint64 ConvertToInt(sint8 * ptr,uint8 len); //Convert ASCII to integer

uint8 calculate(); //compute
uint8 display(); //convert integers back to ASCII and display
uint8 Resetall(); 


#endif