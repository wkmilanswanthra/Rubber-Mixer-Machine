#ifndef	LCDCONFIG_H_
#define LCDCONFIG_H_

/***************************************************************************

The four data lines as well as the two control lines may be
implemented on any available I/O pin of any port.  These are
the connections used for this program:

-----------                   ----------
| ATmega32  |                 |   LCD    |
|           |                 |          |
|        PA7|---------------->|D7        |
|        PA6|---------------->|D6        |
|        PA5|---------------->|D5        |
|        PA4|---------------->|D4        |
|           |                 |D3        |
|           |                 |D2        |
|           |                 |D1        |
|           |                 |D0        |
|           |                 |          |
|        PB3|---------------->|E         |
|        PB2|---------------->|RW        |
|        PB1|---------------->|RS        |
-----------                   ----------

**************************************************************************/

#define LCD_PORT_D7     	PORTB
#define LCD_DDR_D7      	DDRB
#define D7_BIT				7

#define LCD_PORT_D6     	PORTB
#define LCD_DDR_D6      	DDRB
#define D6_BIT				6

#define LCD_PORT_D5     	PORTB
#define LCD_DDR_D5      	DDRB
#define D5_BIT				5

#define LCD_PORT_D4     	PORTB
#define LCD_DDR_D4      	DDRB
#define D4_BIT				4

//lcd Enable pin
#define E_PORT				PORTB
#define E_BIT				1
#define E_DDR				DDRB
//lcd Register Select pin
#define RS_PORT				PORTB
#define RS_BIT				0
#define RS_DDR				DDRB
//lcd Register Select pin
#define RW_PORT				PORTB
#define RW_BIT				2
#define RW_DDR				DDRB
 
#endif // LCDCONFIG_H_