/* UART source file */

#include "uart.h"

/* Global buffer instances for UART*/
uint8_t usart1_rxbuf_storage[USART1_RX_BUF_SIZE];
uint8_t usart1_txbuf_storage[USART1_TX_BUF_SIZE];
volatile usart1_buffer_t usart1_rx_buffer;
volatile usart1_buffer_t usart1_tx_buffer;

void usart1_init(void)
{
	// Register level control
	USART1->CR1 |= USART_CR1_RXNEIE; // Enable RX Not Empty interrupt
	USART1->CR1 |= USART_CR1_TXEIE; // Enable TX Empty interrupt
	USART1->CR1 |= USART_CR1_TCIE; // Enable Transmission Complete interrupt 
	
	// Enable interrupt in NVIC
	NVIC_EnableIRQ(USART1_IRQn); // Letting hardware handle the priority level of the interrupt
	
	usart1_buffer_init(&usart1_rx_buffer, usart1_rxbuf_storage, USART1_RX_BUF_SIZE);
	usart1_buffer_init(&usart1_tx_buffer, usart1_txbuf_storage, USART1_TX_BUF_SIZE);
}

void usart1_buffer_init(volatile usart1_buffer_t *buff, uint8_t *storage, uint16_t size)
{
	buff->buffer = storage;
	buff->size = size;
	buff->head = 0;
	buff->tail = 0;
	buff->count = 0;
	buff->overflow = false;
}
