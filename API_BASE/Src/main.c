/*
 * main.c
 *
 *  Created on: Feb 25, 2023
 *      Author: Phong Nguyen
 */
#include"main.h"
#include "stm32_gpio_driver.h"
#include "core.h"
#include "stm32_delay_timer.h"
#include "core_systick_delay.h"
#include "stm32_usart.h"
#include <string.h>
#define mode_trans 		(1<<3)
#define mode_recev		(1<<2)
void delay(uint32_t t);
void initGPIO();
void initEXT0();
uint32_t count=0;
char arr[]="Hello Phong Nguyen ^.^";
uint8_t buffer[8];
uint8_t pRxBuff='A';
int main(void)
{
	SysClockConfig_100Mhz();
	initGPIO();
//	initEXT0();
//	initTIM2();

//	USART2_Init(mode_trans|mode_recev);
//	USART2_IT_Received_Init();
	Systick_delay_Init();
	//USART2_Transmit_string(arr,strlen(arr));
	while(1)
	{
		//if(GPIO_ReadFromInputPin(GPIOA,GPIO_PIN_0)==1)
		//{
			GPIO_ToggleOutputPin(GPIOD,GPIO_PIN_12);
		//	delay(2000000);
		//	delay_ms(2000);
//			USART2_Transmit_string(arr,strlen(arr));
		Delay_systick_Ms(4000);
//			count++;
		//}
		//	USART2_Received_string(buffer, 8);
		//	USART2_Transmit_1byte(pRxBuff);
	}
}

void delay(uint32_t t)
{
	while(t--);
}

void initGPIO()
{
	//PD12-led on board - OUTPUT GPIO
	GPIO_Handle_t GPIO_LED,GPIO_BTN;
	GPIO_LED.pGPIOx=GPIOD;
	GPIO_LED.GPIO_PinConfig.GPIO_PIN=GPIO_PIN_12;
	GPIO_LED.GPIO_PinConfig.GPIO_MODE=GPIO_MODE_OUT;
	GPIO_LED.GPIO_PinConfig.GPIO_SPEED=GPIO_SPEED_LOW;
	GPIO_LED.GPIO_PinConfig.GPIO_OTYPE=GPIO_OTYPE_PP;
	GPIO_LED.GPIO_PinConfig.GPIO_ITYPE=GPIO_ITYPE_NO;
	GPIO_PeriClockControl(GPIOD,ENABLE);		//clock for gipo
	GPIO_Init(&GPIO_LED);

	//PA0-button on board - INPUT GPIO
	GPIO_BTN.pGPIOx=GPIOA;
	GPIO_BTN.GPIO_PinConfig.GPIO_PIN=GPIO_PIN_0;
	GPIO_BTN.GPIO_PinConfig.GPIO_MODE=GPIO_MODE_IN;
	GPIO_BTN.GPIO_PinConfig.GPIO_SPEED=GPIO_SPEED_LOW;
	GPIO_BTN.GPIO_PinConfig.GPIO_ITYPE=GPIO_ITYPE_NO;
	GPIO_PeriClockControl(GPIOA,ENABLE);
	GPIO_Init(&GPIO_BTN);
}
void initEXT0()
{
	//B1: enable clock cho SYSCFG
	SYSCFG_PCLK_EN();
	//B2: config gpio button ~ o? phia tren - chan ngat PA0
	//B3: chon line ngat line 0 PA0
	SYSCFG->EXTICR[0]&=~(0xF<<0);
	//B4:select rising edge
	EXTI->RTSR|=(1<<0);
	EXTI->FTSR&=~(1<<0);
	//B5: enable line  (bo mask che)
	EXTI->IMR|=(1<<0);
	//B6: priority and start ?? how - nvic core register and i don't know
	//start
	NVIC->ISER[0]|=(1<<6);

}

//from vector table
void EXTI0_IRQHandler(void)
{
	if((EXTI->PR)&(1<<0)) //check pedding bit
	{
		count++;
		GPIO_ToggleOutputPin(GPIOD,GPIO_PIN_12);
		(EXTI->PR)|=(1<<0);	//clear pedding bit

	}
}


