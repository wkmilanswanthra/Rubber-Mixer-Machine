/*
 * global.h
 *
 * Created: 9/22/2016 7:58:03 PM
 *  Author: Toshiba-pc
 */ 
#ifndef GLOBAL_H_
#define GLOBAL_H_

#define MaxNumberOfDigits 16
#define MaxNumberOfOperands 12	//including =
#define MaxNumberOfOperations MaxNumberOfOperands-1 //excluding =

#define IsOperation(n) ((n=='*')||(n=='+')||(n=='-')||(n=='%'))
//enum Flags{Reset=0,StartPoint,AnalyzePoint,CalculatePoint,DisplayPoint,ErrorPoint};
	#define Reset			0
	#define StartPoint		1
	#define AnalyzePoint	2
	#define CalculatePoint	3
	#define DisplayPoint	4
	#define ErrorPoint		5
	
extern uint8 Flag;

#endif 