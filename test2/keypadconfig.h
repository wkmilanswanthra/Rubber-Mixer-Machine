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
#define ROW0_DDR		DDRA
#define ROW1_DDR		DDRA
#define ROW2_DDR		DDRA
#define ROW3_DDR		DDRA
#define LINE0_DDR		DDRA
#define LINE1_DDR		DDRA
#define LINE2_DDR		DDRA
#define LINE3_DDR		DDRA
//ROWs' PORTs
#define ROW0_PORT		PORTA
#define ROW1_PORT		PORTA
#define ROW2_PORT		PORTA
#define ROW3_PORT		PORTA
//LINEs' PINs
#define LINE0_PIN		PINA
#define LINE1_PIN		PINA
#define LINE2_PIN		PINA
#define LINE3_PIN		PINA
//LINES' PULLUP
#define LINE0_PULLUP	PORTA
#define LINE1_PULLUP	PORTA
#define LINE2_PULLUP	PORTA
#define LINE3_PULLUP	PORTA

#endif //KEYPADCONFIG_H_