/*
 * stm32_gpio_driver.c
 *
 *  Created on: Feb 25, 2023
 *      Author: Phong Nguyen
 */
#include "stm32_gpio_driver.h"

//peripheral clock  settup
void GPIO_PeriClockControl(GPIO_RgDef_t *pGPIOx,uint8_t EnorDi)
{
	if(EnorDi==ENABLE)
	{
		if(pGPIOx==GPIOA)
			GPIOA_PCLK_EN();
		else if(pGPIOx==GPIOB)
			GPIOB_PCLK_EN();
		else if(pGPIOx==GPIOC)
			GPIOC_PCLK_EN();
		else if(pGPIOx==GPIOD)
			GPIOD_PCLK_EN();
		else if(pGPIOx==GPIOE)
			GPIOE_PCLK_EN();
		else if(pGPIOx==GPIOH)
			GPIOH_PCLK_EN();
	}
	//else if(EnorDi==DISABLE)
	else
	{
		if(pGPIOx==GPIOA)
			GPIOA_PCLK_DIS();
		else if(pGPIOx==GPIOB)
			GPIOB_PCLK_DIS();
		else if(pGPIOx==GPIOC)
			GPIOC_PCLK_DIS();
		else if(pGPIOx==GPIOD)
			GPIOD_PCLK_DIS();
		else if(pGPIOx==GPIOE)
			GPIOE_PCLK_DIS();
		else if(pGPIOx==GPIOH)
			GPIOH_PCLK_DIS();
	}
}

//init and de-init
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	//1.Config the mode of GPIO Pin (I/O/Altenate)
		uint32_t temp=0; //temp.register // do bien temp la 32 bit nen no se mo rong !!

	if(pGPIOHandle->GPIO_PinConfig.GPIO_MODE <= GPIO_MODE_ANALOG)
	{
		temp=(pGPIOHandle->GPIO_PinConfig.GPIO_MODE << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PIN));
		pGPIOHandle->pGPIOx->MODER &=~(0x03<<(2*pGPIOHandle->GPIO_PinConfig.GPIO_PIN)); //clearing
		pGPIOHandle->pGPIOx->MODER |=temp;
 	}
	else
	{
		//this part for interrupt
	}
	temp=0;
	//2.Config speed
	temp=(pGPIOHandle->GPIO_PinConfig.GPIO_SPEED << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PIN));
	pGPIOHandle->pGPIOx->OSPEEDR &=~(0x03<<(2*pGPIOHandle->GPIO_PinConfig.GPIO_PIN)); //clearing
	pGPIOHandle->pGPIOx->OSPEEDR |=temp;

	temp=0;
	//3.Config pupd
	temp=(pGPIOHandle->GPIO_PinConfig.GPIO_ITYPE << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PIN));
	pGPIOHandle->pGPIOx->PUPDR &=~(0x03<<(2*pGPIOHandle->GPIO_PinConfig.GPIO_PIN)); //clearing
	pGPIOHandle->pGPIOx->PUPDR |=temp;

	temp=0;

	//4.Config otype
	temp=(pGPIOHandle->GPIO_PinConfig.GPIO_OTYPE << (pGPIOHandle->GPIO_PinConfig.GPIO_PIN));
	pGPIOHandle->pGPIOx->OTYPER &=~(0x01<<(pGPIOHandle->GPIO_PinConfig.GPIO_PIN)); //clearing
	pGPIOHandle->pGPIOx->OTYPER |=temp;

	temp=0;
	//6.Config altenate funtionally
	if(pGPIOHandle->GPIO_PinConfig.GPIO_MODE ==GPIO_MODE_ALTFN)
	{
		uint32_t temp1,temp2;
		temp1=pGPIOHandle->GPIO_PinConfig.GPIO_PIN	/8;
		temp2=pGPIOHandle->GPIO_PinConfig.GPIO_PIN	%8;
		temp=(pGPIOHandle->GPIO_PinConfig.GPIO_ALTF)<<(4*temp2);
		pGPIOHandle->pGPIOx->AFR[temp1]&=~(0xF<<(4*temp2));//clearing
		pGPIOHandle->pGPIOx->AFR[temp1]|=temp;   //select AFuntion

	}
}

void GPIO_DeInit(GPIO_RgDef_t *pGPIOx)
{
	if(pGPIOx==GPIOA)
		GPIOA_REG_RESET();
	else if(pGPIOx==GPIOB)
		GPIOB_REG_RESET();
	else if(pGPIOx==GPIOC)
		GPIOC_REG_RESET();
	else if(pGPIOx==GPIOD)
		GPIOD_REG_RESET();
	else if(pGPIOx==GPIOE)
		GPIOE_REG_RESET();
	else if(pGPIOx==GPIOH)
		GPIOH_REG_RESET();
}
//Data read and write
uint8_t GPIO_ReadFromInputPin(GPIO_RgDef_t *pGPIOx,uint8_t GPIO_PIN)
{
	uint8_t value;

	value=(uint8_t)((pGPIOx->IDR>>GPIO_PIN)&0x01);
	return value;
}
uint16_t GPIO_ReadFromInputPort(GPIO_RgDef_t *pGPIOx)
{
	uint16_t value;

	value=(uint16_t)(pGPIOx->IDR);
	return value;
}
void GPIO_WritetoOutPin(GPIO_RgDef_t *pGPIOx,uint8_t GPIO_PIN,uint8_t value)
{
	if(value==SET)
	{
		pGPIOx->ODR|=(1<<GPIO_PIN);
	}
	else
	{
		pGPIOx->ODR&=~(1<<GPIO_PIN);
	}

}
void GPIO_WritetoOutPort(GPIO_RgDef_t *pGPIOx,uint8_t value)
{
	pGPIOx->ODR=value;
}
void GPIO_ToggleOutputPin(GPIO_RgDef_t *pGPIOx,uint8_t GPIO_PIN)
{
	pGPIOx->ODR^=(1<<GPIO_PIN);
}

//IRQ config and IRQ handling
void GPIO_IRQConfig(void)
{

}
void GPIO_IRQHandling(void)
{

}
