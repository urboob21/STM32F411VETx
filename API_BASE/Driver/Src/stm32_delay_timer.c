/*
 * stm32_delay_timer.c
 *
 *  Created on: Feb 27, 2023
 *      Author: Phong Nguyen
 */
#include "stm32_delay_timer.h"

void initTIM2()
{
	//B1: enable clock timer
	TIM2_PCLK_EN();
	//caculate f_cnt=f_clk/(psc+1)
	//B2: sett ARR
	TIM2->ARR=0xFFFF;
	//B3: set PSC
	TIM2->PSC=100-1;
	//B4:set up count DIR of CR1
	TIM2->CR1&=~(1<<4);
	//B5: set enable timer CEN of CR1
	TIM2->CR1|=(1<<0);
	//B6: enable reset when tran UG of EGR
	TIM2->EGR|=(1<<0);
}
void delay_ms(uint32_t t)
{
	initTIM2();
	while(t)
	{
		TIM2->CNT=0U;
		while((TIM2->CNT)<1000);
		t--;
	}
	TIM2_REG_RESET();
}
