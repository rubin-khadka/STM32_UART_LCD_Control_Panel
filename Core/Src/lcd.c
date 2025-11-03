/* LCD Source file */

#include "lcd.h"

void lcd_write_command(uint8_t param)
{
	uint8_t i;
	
	// do busy check here
	RS(0);
	RW(0);
	
}

void lcd_process_4bit(uint8_t data)
{
	// Set data pins using direct bit operation
	// shifted to get 1/0 value for proper macro behaviour
	D4((data & 0x01) >> 0); 
	D5((data & 0x02) >> 1);
	D6((data & 0x04) >> 2);
	D7((data & 0x08) >> 3);
	
	// Create small pulse, LCD samples data on the falling edge of EN
	EN(1);
	for(uint8_t i; i<10; i++); // wait for signal to stablize
	EN(0); // data get latched
}