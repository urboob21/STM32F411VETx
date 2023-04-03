/*
 * stm32_clock.c
 *
 *  Created on: Feb 25, 2023
 *      Author: Phong Nguyen
 */
#include"stm32_clock.h"
#include "stm32f411.h"
#define PLL_M 8		// /8
#define PLL_N 200  //*200
#define PLL_P 0 // /2
void SysClockConfig_100Mhz()
{
	//1.Enable HSE and wait HSE ready
	RCC->CR|=1<<16;
	while(!((RCC->CR)&(1<<17)));
	//2. Set power and voltage
	RCC->APB1ENR|=1<<28;
	PWR->CR|=3<<14;
	//3.Flash config
	FLASH->ACR|=(1<<11)|(1<<10)|(1<<8)|(3<<0);
	//4.Config prescaler
	RCC->CFGR&=~(1<<7); //bit CFGR[7:3]=0xxx
	RCC->CFGR|=(4<<12);
	RCC->CFGR&=~(1<<15);
	//5.Config MAIN PLL
	RCC->PLLCFGR = (PLL_M <<0) | (PLL_N << 6) | (PLL_P <<16) | (1<<22);
	//6.Enable PLL and wait PLL ready
	RCC->CR|=(1<<24);
	while(!((RCC->CR)&(1<<25)));
	//7.Set PLL for SYSCLK
	RCC->CFGR|=(2<<0);
	while(!((RCC->CFGR)&(2<<2)));

	//	HSE=8Mhz , all run with 100Mhz ,
	//only APB1-peripheral run with 50Mhz,timer 100mhz (Advanced Peripheral Buses 1,2)
}


