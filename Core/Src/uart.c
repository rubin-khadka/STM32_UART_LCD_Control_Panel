/* UART source file */

#include "uart.h"

/* Global buffer instances for UART*/
uint8_t usart1_rxbuf_storage[USART1_RX_BUF_SIZE];
uint8_t usart1_txbuf_storage[USART1_TX_BUF_SIZE];
volatile usart1_buffer_t usart1_rx_buf;
volatile usart1_buffer_t usart1_tx_buf;

void usart1_init(void)
{
	// Register level control
	USART1->CR1 |= USART_CR1_RXNEIE; // Enable RX Not Empty interrupt
	// USART1->CR1 |= USART_CR1_TXEIE; // Enable TX Empty interrupt
	// USART1->CR1 |= USART_CR1_TCIE; // Enable Transmission Complete interrupt 
	
	// Enable interrupt in NVIC
	NVIC_EnableIRQ(USART1_IRQn); // Letting hardware handle the priority level of the interrupt
	
	usart1_buffer_init(&usart1_rx_buf, usart1_rxbuf_storage, USART1_RX_BUF_SIZE);
	usart1_buffer_init(&usart1_tx_buf, usart1_txbuf_storage, USART1_TX_BUF_SIZE);
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

bool usart1_buffer_full(volatile usart1_buffer_t *buff)
{
	return (buff->count >= buff->size);
}


bool usart1_buffer_write(volatile usart1_buffer_t *buff, uint8_t data)
{
	if (usart1_buffer_full(buff))
	{
		buff->overflow = true;
		return false;
	}
	
	buff->buffer[buff->head] = data;
	buff->head = (buff->head + 1) % buff->size;
	buff->count++;
	
	return true;
}

uint8_t usart1_buffer_read(volatile usart1_buffer_t *buff)
{
	if (usart1_buffer_isempty(buff))
	{
		return 0;
	}
	
	uint8_t data = buff->buffer[buff->tail];
	buff->tail = (buff->tail + 1) % buff->size;
	buff->count--;
	
	return data;
}


/* Interrupt Function */
void usart1_rx_interrupt(void)
{
	uint8_t data = USART1->DR;
	usart1_buffer_write(&usart1_rx_buf, data);
}

void usart1_tx_interrupt(void)
{
	uint8_t data = usart1_buffer_read(&usart1_tx_buf);
	USART1->DR = data;
}






