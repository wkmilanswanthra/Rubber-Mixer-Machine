#ifndef LCD__H_
#define LCD__H_

#define F_CPU	1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcdconfig.h"


//LCD instructions
#define clearDisplay        0b00000001          // replace all characters with ASCII 'space'
#define lcd_Home            0b00000010          // return cursor to first position on first line
#define lcd_EntryMode       0b00000110          // shift cursor from left to right on read/write
#define lcd_DisplayOff      0b00001000          // turn display off
#define lcd_DisplayOn       0b00001100          // display on, cursor off, don't blink character
#define lcd_FunctionReset   0b00110000          // reset the LCD
#define lcd_FunctionSet4bit 0b00101000          // 4-bit data, 2-line display, 5 x 7 font
#define lcd_SetCursor       0b10000000          // set cursor position
#define lcd_showcursor		0b00001111			//show cursor position

//Function Prototypes
void lcd_write(char Byte);
void lcd_write_instruction(char command);
void lcd_write_character(char Data);
void lcd_write_string(char *string);
void lcd_init(void);
void lcd_clearDisplay(void);
void lcd_gotoxy(char pos, char line);


#endif   /*__LCD__H_*/