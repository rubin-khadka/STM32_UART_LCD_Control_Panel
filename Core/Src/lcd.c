/* LCD Source file */

#include "lcd.h"

void lcd_init(void)
{
	RS(0);
	RW(0);
	
	lcd_process_4bit(0x2); // 4 bit more
	lcd_write_command(0x28); // 4 bit 2 line
	lcd_write_command(0xC); // bit2=on_off, bit1= cursor on, bit0= display_blink
}

void lcd_write_command(uint8_t param)
{
	// do busy check here
	RS(0);
	RW(0);
	
	lcd_process_4bit(param >>4); // High nibble first
	lcd_process_4bit(param & 0xF); // Low nibble second
	
	for(uint8_t i=0; i<20; i++); // small delay, will replace by timer later
}

void lcd_write_data(uint8_t param)
{
	// do busy check here
	RS(1);
	RW(0);
	
	lcd_process_4bit(param >>4); // High nibble first
	lcd_process_4bit(param & 0xF); // Low nibble second
	
	for(uint8_t i=0; i<20; i++); // small delay, will replace by timer later
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
	for(uint8_t i=0; i<10; i++); // wait for signal to stablize
	EN(0); // data get latched
}