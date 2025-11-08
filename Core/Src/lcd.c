/* LCD Source file */

#include "lcd.h"

void lcd_init(void)
{
	// Set control pins for commmand mode
	RS(0); // Command mode 
	RW(0); // Write mode
	
	// Wait for LCD power stabilization
	// Manual initialisation sequence
	HAL_Delay(50);
	lcd_process_4bit(0x03);
	HAL_Delay(5);           
	lcd_process_4bit(0x03);  
	HAL_Delay(1);           
	lcd_process_4bit(0x03);  
	HAL_Delay(1);      
	
	// Switch to 4 bit mode
	lcd_process_4bit(0x02);  // Send 0010 (Switch to 4-bit mode)
	HAL_Delay(1);  
	
	lcd_write_command(0x28); // 4-bit, 2-line, 5x8
	lcd_write_command(0x0E); // Display ON
	lcd_write_command(0x01); // Clear display
	HAL_Delay(2);
	lcd_write_command(0x06); // Entry mode
}

void lcd_write_command(uint8_t param)
{
	// do busy check here
	RS(0);
	RW(0);
	
	lcd_process_4bit(param >>4); // High nibble first
	lcd_process_4bit(param & 0xF); // Low nibble second
	
	HAL_Delay(2); // small delay, will replace by timer later
}

void lcd_write_data(uint8_t param)
{
	// do busy check here
	HAL_Delay(5);
	RS(1);
	RW(0);
	
	lcd_process_4bit(param >>4); // High nibble first
	lcd_process_4bit(param & 0xF); // Low nibble second
	
	HAL_Delay(5); // small delay, will replace by timer later
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
	HAL_Delay(2); // wait for signal to stablize
	EN(0); // data get latched
}

void lcd_set_cursor(uint8_t row, uint8_t col)
{
	lcd_write_command((row & 0x01) ? (0xC0 | (col & 0x0F)) : (0x80 | (col & 0x0F)));
}

void lcd_print(const char *str) 
{
	while(*str) 
	{
		lcd_write_data(*str++);
	}
}

void lcd_clear(void)
{
	lcd_write_command(0x01);
}
