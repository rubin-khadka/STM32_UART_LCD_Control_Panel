/* LCD Header file */

#ifndef LCD_H
#define LCD_H

#include "main.h"

// LCD Pin Macros
#define RS(x) (x==1 ? (HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET)) : (HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET)))
#define RW(x) (x==1 ? (HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_SET)) : (HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET)))
#define EN(x) (x==1 ? (HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET)) : (HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET)))
#define D4(x) (x==1 ? (HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_SET)) : (HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_RESET)))
#define D5(x) (x==1 ? (HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, GPIO_PIN_SET)) : (HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, GPIO_PIN_RESET)))
#define D6(x) (x==1 ? (HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, GPIO_PIN_SET)) : (HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, GPIO_PIN_RESET)))
#define D7(x) (x==1 ? (HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, GPIO_PIN_SET)) : (HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, GPIO_PIN_RESET)))

// LCD Function prototypes
void lcd_init(void);
void lcd_write_command(uint8_t param);
void lcd_write_data(uint8_t param);
void lcd_process_4bit(uint8_t data);

#endif