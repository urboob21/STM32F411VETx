/*
 * stm32_usart.h
 *
 *  Created on: Feb 27, 2023
 *      Author: Phong Nguyen
 */

#ifndef INC_STM32_USART_H_
#define INC_STM32_USART_H_
#include "stm32f411.h"
#include "stm32_gpio_driver.h"
#include "core.h"
void GPIO_USART2_Init();
void USART2_Init(uint8_t mode_usart);
void USART2_Transmit_1byte(uint8_t byte_out);
void USART2_Transmit_string(uint8_t* sbyte_out, uint8_t len);
uint8_t USART2_Received_1byte();
void USART2_Received_string(uint8_t* sbyte_in, uint8_t len);
void USART2_IT_Received_Init();



#endif /* INC_STM32_USART_H_ */
