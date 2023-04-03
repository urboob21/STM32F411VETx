/*
 * stm32_delay_timer.h
 *
 *  Created on: Feb 27, 2023
 *      Author: Phong Nguyen
 */

#ifndef INC_STM32_DELAY_TIMER_H_
#define INC_STM32_DELAY_TIMER_H_
#include "stm32f411.h"

void initTIM2();
void delay_ms(uint32_t t);


#endif /* INC_STM32_DELAY_TIMER_H_ */
