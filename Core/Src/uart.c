/* UART source file */

#include "uart.h"

void uart_init(void)
{
	NVIC_EnableIRQ(USART1_IRQn); // Enable interrupt in NVIC
	// __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
	USART1->CR1 |= USART_CR1_RXNEIE; // Enable RX interrupt in USART
}
