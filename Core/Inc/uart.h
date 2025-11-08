/* UART header file */

#ifndef UART_H
#define UART_H

/* Private includes*/
#include "lcd.h"

/* Define buffer size */
#define USART1_RX_BUF_SIZE 256  // RX buffer size
#define USART1_TX_BUF_SIZE 256  // TX buffer size

/* Circular buffer structure for UART */
typedef struct
{
	uint8_t *buffer; // Pointer to buffer memory
	uint16_t size; 	// Total buffer size
	volatile uint16_t head; // Write Position
	volatile uint16_t tail; // Read Position
	volatile uint16_t count; // Number of bytes in the buffer
	volatile bool overflow; // Overflow flag
} usart1_buffer_t;

/* External declarations */
extern volatile usart1_buffer_t usart1_rx_buf;
extern volatile usart1_buffer_t usart1_tx_buf;

#define usart1_buffer_isempty(buff) (((buff)->head == (buff)->tail) ? true : false)

/* Private function definition */
void usart1_init(void);

/* Core buffer functions */
void usart1_buffer_init(volatile usart1_buffer_t *buff, uint8_t *storage, uint16_t size);
bool usart1_buffer_full(volatile usart1_buffer_t *buff);
bool usart1_buffer_write(volatile usart1_buffer_t *buff, uint8_t data);
uint8_t usart1_buffer_read(volatile usart1_buffer_t *buff);

/* Interrupt Function */
void usart1_rx_interrupt(void);
void usart1_tx_interrupt(void);

#endif