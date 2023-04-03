/*
 * stm32_usart.c
 *
 *  Created on: Feb 27, 2023
 *      Author: Phong Nguyen
 */

#include "stm32_usart.h"
#include"main.h"
extern uint8_t pRxBuff;

void GPIO_USART2_Init()
{
	//AF7 , PA2 TX , PA3RX
	GPIO_PeriClockControl(GPIOA, ENABLE);
	GPIO_Handle_t	GPIO_TX1,GPIO_RX1;
	//PA2 TX- output
	GPIO_TX1.pGPIOx=GPIOA;
	GPIO_TX1.GPIO_PinConfig.GPIO_PIN=GPIO_PIN_2;
	GPIO_TX1.GPIO_PinConfig.GPIO_SPEED=GPIO_SPEED_HIGH;
	GPIO_TX1.GPIO_PinConfig.GPIO_MODE=GPIO_MODE_ALTFN;
	GPIO_TX1.GPIO_PinConfig.GPIO_ITYPE=GPIO_ITYPE_PU;
	GPIO_TX1.GPIO_PinConfig.GPIO_OTYPE=GPIO_OTYPE_PP;
	GPIO_TX1.GPIO_PinConfig.GPIO_ALTF=GPIO_ALTF_AF7;

	//PA3 RX- input
	GPIO_RX1.pGPIOx=GPIOA;
	GPIO_RX1.GPIO_PinConfig.GPIO_PIN=GPIO_PIN_3;
	GPIO_RX1.GPIO_PinConfig.GPIO_SPEED=GPIO_SPEED_HIGH;
	GPIO_RX1.GPIO_PinConfig.GPIO_MODE=GPIO_MODE_ALTFN;
	GPIO_RX1.GPIO_PinConfig.GPIO_ITYPE=GPIO_ITYPE_PU;
	GPIO_RX1.GPIO_PinConfig.GPIO_OTYPE=GPIO_OTYPE_PP;
	GPIO_RX1.GPIO_PinConfig.GPIO_ALTF=GPIO_ALTF_AF7;
	//
	GPIO_Init(&GPIO_TX1);
	GPIO_Init(&GPIO_RX1);
}
void USART2_Init(uint8_t mode_usart)
{
//	uint32_t usart_div=0;
//	uint32_t DIV_Man,DIV_Frac;
	//B1:Enable CLK
	USART2_PCLK_EN();
	//B2: init GPIO RX TX
	GPIO_USART2_Init();
	//B3: config usart
	USART2->CR1|=mode_usart; 	//mode trans/receiv
	USART2->CR1&=~(1<<12);		//word leng
						//stop bit, parity,..
	//B4:Cal baudrate
	/*
	 * PLCK (APB1=50Mhz)
	 * Baudrate=9600
	 * OVER=0-> sample =16 (bit 15 CR1)
	 */
//	usart_div=100000000/(16*9600); //16.543 -> 0.16543
//	DIV_Man=
	USART2->BRR|=(651<<4)|(7<<0);

	//B5: enable USART1
	USART2->CR1|=(1<<13);
}
void USART2_Transmit_1byte(uint8_t byte_out)
{
	//check TXE
	while(!(((USART2->SR)>>7)&0x01));
	USART2->DR=byte_out;
	//check TC
	while(!(((USART2->SR)>>6)&0x01));			//while(1); khi co=1 dung cho, while(~(1)): khi 1 thi out
	//while (!(USART2->SR & (1<<6)));
}
//do dai chuoi khong tinh ky tu rong
void USART2_Transmit_string(uint8_t* sbyte_out, uint8_t len)
{
	for(int i=0;i<len;i++)
		USART2_Transmit_1byte(sbyte_out[i]);
}
uint8_t USART2_Received_1byte()
{
	uint8_t byte_in;
	//check RXNE 1:ready to be read
	while(!(((USART2->SR)>>5)&0x01));
	byte_in=USART2->DR;
	return byte_in;
}
void USART2_Received_string(uint8_t* sbyte_in, uint8_t len)
{
	for(int i=0;i<len;i++)
		sbyte_in[i]=USART2_Received_1byte();
}

void USART2_IT_Received_Init()
{
	//B1: enable flag interrupt UASRT
	USART2->CR1|=(1<<5);
	//B2: enable USART2 IRQ number=38; - line NVIC
	NVIC->ISER[1]|=(1<<6);
	//B3: clear pending state in nvic regis
	NVIC->ICPR[1]|=(1<<6);
	//B4: enable interrupt
	__asm volatile("cpsie i");

}

void USART2_IRQHandler(void)
{

	pRxBuff=USART2_Received_1byte();
	NVIC->ICPR[1]|=(1<<7);
}
