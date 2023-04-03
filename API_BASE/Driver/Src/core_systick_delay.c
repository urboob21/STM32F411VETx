/*
 * core_systick_delay.c
 *
 *  Created on: Feb 27, 2023
 *      Author: Phong Nguyen
 */
#include"core_systick_delay.h"
static volatile uint32_t usTicks;
void Systick_delay_Init()
{
	//B1: select processor clock AHB=max 100MHz
	SYSTICK->CSR|=(1<<2);
	//B2: reload value: 1cnt = 100*1/(100Mhz)=1us
	SYSTICK->RVR=100;
	//B3:enable/disable systick interrupt
	SYSTICK->CSR|=(1<<1);
}
void Delay_systick_Us(uint32_t t)
{
	//B1: enable systick
	SYSTICK->CSR|=(1<<0);
	usTicks=t;
	while(usTicks); //while stick tick dem 1us -> ngat ? check t --
	//B2:  khi dem du t*1us ( t la so lan nhay vao interruppt 1us), disable
	SYSTICK->CSR&=~(1<<0);
}
void Delay_systick_Ms(uint32_t t)
{
	while(t--)
	{
		Delay_systick_Us(1000);
		//t=t-1;
	}
}
void SysTick_Handler()
{
	if(usTicks!=0)
		usTicks--;
}

