/*
 * dc.h 
 */ 

#define DC_PRT PORTD
#define DC_DDR DDRD
#define DC_PIN PIND

void dc_init();
void dc_clk(int);
void dc_aclk(int);
void dc_stp();
void acvt_mixer();

void acvt_mixer(){
	dc_init();
	dc_clk(2500);
	dc_aclk(2500);
	dc_stp();

	
}

void dc_init(){
	DC_DDR |= 0x03; //Set pin D0 and D1 to output
	DC_PRT |= (0X00 &~(1<<0)); //Set pin D0 to low to avoid any initial movements
	DC_PRT |= (0X00 &~(1<<0)); //Set pin D1 to low to avoid any initial movements
}

void dc_stp(){
	DC_PRT &= 0xFC; // Set the pins D0 and D1 to low to stop the motor
}

void dc_aclk(int ms){
	DC_PRT |= (1<<0); //Set pin D0 to high for clock wise rotation
	while (ms--)
	{
		_delay_ms(1);
	}
	dc_stp();
}

void dc_clk(int ms){
	DC_PRT |= (1<<1); //Set pin D0 to high for clock wise rotation
	while (ms--)
	{
		_delay_ms(1);
	}
	dc_stp();
}