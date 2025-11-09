/* TIMER1 source file */

#include "timer1.h"

/* Global variable */
volatile uint8_t lcd_busy = 0;

void timer1_init(void)
{
	// Enable timer 1 clock
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	
	// Configure for 100 microsecond base (8 MHz timer clock)
	TIM1->PSC = 799;
	TIM1->CNT = 0;
	
	// Enable update interrupt
	TIM1->DIER |= TIM_DIER_UIE;
	
	//Clear any pending interrupt flag
	TIM1->SR &= ~TIM_SR_UIF;
	
	// Configure NVIC
	NVIC_EnableIRQ(TIM1_UP_IRQn);
}

void timer1_delay_ms(uint32_t ms_delay)
{
	// Stop timer if running
	TIM1->CR1 &= ~TIM_CR1_CEN; 
	
	// Clear any pending interrupt
	TIM1->SR &= ~TIM_SR_UIF;
	
	// Set ARR for desired delay (100 microsecond base)
	uint32_t ticks = ms_delay * 10;    // Convert ms to 100µs ticks
	TIM1->ARR = ticks - 1;             // ARR = (ticks - 1)
	TIM1->CNT = 0;                     // Reset to 0
	
	// Start timer and set busy flag
	lcd_busy = 1;
	TIM1->CR1 |= TIM_CR1_CEN;
	
}

void TIM1_UP_IRQHandler(void)
{
	if(TIM1->SR & TIM_SR_UIF) // Check if interrupt cause by timer
	{
		TIM1->SR &= ~TIM_SR_UIF; // Clear interrupt flag
		TIM1->CR1 &= ~TIM_CR1_CEN; // Stop timer
		
		lcd_busy = 0; // Set lcd to not busy mode
	}
}


