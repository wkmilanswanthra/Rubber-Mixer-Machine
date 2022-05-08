

#include "lcd.h"

void lcd_init(void)
{
	
	// configure the microprocessor pins for the data lines
    LCD_DDR_D7 |= (1U<<D7_BIT);                  // 4 data lines - output
    LCD_DDR_D6 |= (1U<<D6_BIT);
    LCD_DDR_D5 |= (1U<<D5_BIT);
    LCD_DDR_D4 |= (1U<<D4_BIT);

// configure the microprocessor pins for the control lines
    E_DDR  |= (1U<<E_BIT);                    // E line - output
    RS_DDR |= (1U<<RS_BIT);                   // RS line - output
	RW_DDR |= (1U<<RW_BIT);					  // RW line - output

// Power-up delay
    _delay_ms(100);                           // initial 40 mSec delay

/* At this point the LCD module is in the 8-bit mode and it is expecting to receive  
   8 bits of data, one bit on each of its 8 data lines, each time the 'E' line is pulsed.

 Since the LCD module is wired for the 4-bit mode, only the upper four data lines are connected to 
   the microprocessor and the lower four data lines are typically left open.  Therefore, when 
   the 'E' line is pulsed, the LCD controller will read whatever data has been set up on the upper 
   four data lines and the lower four data lines will be high (due to internal pull-up circuitry).

 Fortunately the 'FunctionReset' instruction does not care about what is on the lower four bits so  
   this instruction can be sent on just the four available data lines and it will be interpreted 
   properly by the LCD controller.  The 'lcd_write' subroutine will accomplish this if the 
   control lines have previously been configured properly.
*/
// Set up the RS and E lines for the 'lcd_write' subroutine.
    RS_PORT &= ~(1U<<RS_BIT);					  // select the Instruction Register (RS low)
    E_PORT  &= ~(1U<<E_BIT);					  // make sure E is initially low

// Reset the LCD controller
    lcd_write(lcd_FunctionReset);                 // first part of reset sequence
    _delay_ms(10);                                // 4.1 mS delay (min)

    lcd_write(lcd_FunctionReset);                 // second part of reset sequence
    _delay_us(200);                               // 100uS delay (min)

    lcd_write(lcd_FunctionReset);                 // third part of reset sequence
    _delay_us(200);                               // this delay is omitted in the data sheet

/* Preliminary Function Set instruction - used only to set the 4-bit mode.
 The number of lines or the font cannot be set at this time since the controller is still in the
  8-bit mode, but the data transfer mode can be changed since this parameter is determined by one 
  of the upper four bits of the instruction.
 */
    lcd_write(lcd_FunctionSet4bit);               // set 4-bit mode
    _delay_us(80);                                // 40uS delay (min)

// Function Set instruction
    lcd_write_instruction(lcd_FunctionSet4bit);   // set mode, lines, and font
    _delay_us(80);                                // 40uS delay (min)

/* The next three instructions are specified in the data sheet as part of the initialization routine, 
  so it is a good idea (but probably not necessary) to do them just as specified and then redo them 
  later if the application requires a different configuration.
*/

// Display On/Off Control instruction
    lcd_write_instruction(lcd_DisplayOff);        // turn display OFF
    _delay_us(80);                                // 40uS delay (min)

// Clear Display instruction
    lcd_write_instruction(clearDisplay);          // clear display RAM
    _delay_ms(4);                                 // 1.64 mS delay (min)

//  Entry Mode Set instruction
    lcd_write_instruction(lcd_EntryMode);         // set desired shift characteristics
    _delay_us(80);                                // 40uS delay (min)

/* This is the end of the LCD controller initialization as specified in the data sheet, but the display
  has been left in the OFF condition.  This is a good time to turn the display back ON.
 */
// Display On/Off Control instruction
    lcd_write_instruction(lcd_DisplayOn);         // turn the display ON
    _delay_us(80);                                // 40uS delay (min)
}


void lcd_write_string(char *string)
{
	char i = 0;									  // character counter*/
    while (string[i] != '\0')
    {
        lcd_write_character(string[i]);
        i++;
        _delay_us(80);							  // 40 uS delay (min)
    }
}


void lcd_write_character(char Data)
{
	RS_PORT |= (1U<<RS_BIT);                  // select the Data Register (RS high)
    E_PORT  &= ~(1U<<E_BIT);                  // make sure E is initially low
    lcd_write(Data);						  // write the upper 4-bits of the data
    lcd_write(Data << 4);					  // write the lower 4-bits of the data
}

void lcd_write_instruction(char command)
{
	RS_PORT &= ~(1U<<RS_BIT);                 // select the Instruction Register (RS low)
    E_PORT  &= ~(1U<<E_BIT);                  // make sure E is initially low
    lcd_write(command);						  // write the upper 4-bits of the data
    lcd_write(command << 4);                  // write the lower 4-bits of the data
}

void lcd_write(char Byte)
{
	LCD_PORT_D7 &= ~(1<<D7_BIT);                        // assume that data is '0'
    
	if (Byte & (1U<<D7_BIT))
	{
		LCD_PORT_D7 |= (1<<D7_BIT);					 // make data = '1' if necessary
	}
	LCD_PORT_D6 &= ~(1<<D6_BIT);                        // repeat for each data bit
    
	if (Byte & (1U<<D6_BIT))
	{
		 LCD_PORT_D6 |= (1U<<D6_BIT);
	}
    LCD_PORT_D5 &= ~(1U<<D5_BIT);
    
	if (Byte & (1U<<D5_BIT))
	{ 
		LCD_PORT_D5 |= (1U<<D5_BIT);
	}
    LCD_PORT_D4 &= ~(1U<<D4_BIT);
    
	if (Byte & (1U<<D4_BIT))
	{ 
		LCD_PORT_D4 |= (1U<<D4_BIT);
	}
// write the data
                                                    // 'Address set-up time' (40 nS)
    E_PORT |= (1U<<E_BIT);							// Enable pin high
    _delay_us(1);                                   // implement 'Data set-up time' (80 nS) and 'Enable pulse width' (230 nS)
    E_PORT &= ~(1U<<E_BIT);							// Enable pin low
    _delay_us(1);                                   // implement 'Data hold time' (10 nS) and 'Enable cycle time' (500 nS)
}


void lcd_gotoxy (char pos, char line)				//line = 0 or 1	
{
	 lcd_write_instruction((0x80|(line<<6))+pos);
	_delay_us (50);
}

void lcd_clearDisplay(void)	 
{
	lcd_write_instruction(clearDisplay);
	_delay_ms (2);
}