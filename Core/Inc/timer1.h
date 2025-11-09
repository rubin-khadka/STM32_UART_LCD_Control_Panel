/* TIMER1 Header file */

#ifndef TIMER1_H
#define TIMER1_H

/* Private Include definitions */
#include "main.h"
#include "stm32f1xx_hal.h"
#include "stdbool.h"

extern volatile uint8_t lcd_busy;
	
/* Function prototypes */
void timer1_init(void);
void timer1_delay_ms(uint32_t ms_delay);
	
#endif