/*
 * core_systick_delay.h
 *
 *  Created on: Feb 27, 2023
 *      Author: Phong Nguyen
 */

#ifndef INC_CORE_SYSTICK_DELAY_H_
#define INC_CORE_SYSTICK_DELAY_H_
#include "core.h"
void Systick_delay_Init();
void Delay_systick_Us(uint32_t t);
void SysTick_Handler();
void Delay_systick_Ms(uint32_t t);

#endif /* INC_CORE_SYSTICK_DELAY_H_ */
