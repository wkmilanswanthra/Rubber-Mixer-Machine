#ifndef KEYPADCONFIG_H_
#define KEYPADCONFIG_H_

#include <avr/io.h>
//keypad pins
#define ROW0		0
#define ROW1		1
#define ROW2		2
#define ROW3		3
#define LINE0		4
#define LINE1		5
#define LINE2		6
#define LINE3		7
//KEYPAD Direction
#define ROW0_DDR		DDRD
#define ROW1_DDR		DDRD
#define ROW2_DDR		DDRD
#define ROW3_DDR		DDRD
#define LINE0_DDR		DDRD
#define LINE1_DDR		DDRD
#define LINE2_DDR		DDRD
#define LINE3_DDR		DDRD
//ROWs' PORTs
#define ROW0_PORT		PORTD
#define ROW1_PORT		PORTD
#define ROW2_PORT		PORTD
#define ROW3_PORT		PORTD
//LINEs' PINs
#define LINE0_PIN		PIND	
#define LINE1_PIN		PIND
#define LINE2_PIN		PIND
#define LINE3_PIN		PIND
//LINES' PULLUP
#define LINE0_PULLUP	PORTD
#define LINE1_PULLUP	PORTD
#define LINE2_PULLUP	PORTD
#define LINE3_PULLUP	PORTD

#endif //KEYPADCONFIG_H_