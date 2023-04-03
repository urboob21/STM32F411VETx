/*
 * stm32f411.h
 *
 *  Created on: Feb 25, 2023
 *      Author: Phong Nguyen
 */

#ifndef INC_STM32F411_H_
#define INC_STM32F411_H_


#include <stdint.h>
//
#define __vo volatile


////
#define ENABLE 1
#define DISABLE 0
#define SET ENABLE
#define RESET DISABLE
/*!< Peripheral memory map */
// Peripheral_memory_map-----base address of Flash , SRAM , ROM memories
#define FLASH_BASEADDR			0x08000000U
#define SRAM1_BASEADDR			0x20000000U
#define ROM_BASEADDR			0x1FFF0000U
#define SRAM 					SRAM1_BASEADDR

// ABHx and APBx Bus Peripheral base address
#define PERIPH_BASEADDR			0x40000000U
#define APB1PERIPH_BASEADDR		PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR		0x40010000U
#define AHB1PERIPH_BASEADDR		0x40020000U
#define AHB2PERIPH_BASEADDR		0x50000000U

/*!< AHB1 peripherals */
// Base address of peripherals which hanging on AHB1
#define GPIOA_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0000U)
#define GPIOB_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0400U)
#define GPIOC_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0800U)
#define GPIOD_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0C00U)
#define GPIOE_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1000U)
#define GPIOH_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1C00U)

#define RCC_BASEADDR			(AHB1PERIPH_BASEADDR + 0x3800U)

#define FLASH_R_BASEADDR		(AHB1PERIPH_BASEADDR + 0x3C00U)
/*!< AHB2 peripherals */


// Base address of peripherals which hanging on AHB2

/*!< APB1 peripherals */
// Base address of peripherals which hanging on APB1
#define TIM2_BASEADDR			(APB1PERIPH_BASEADDR)
#define USART2_BASEADDR			(APB1PERIPH_BASEADDR +0x4400U)
/*!< APB2 peripherals */
#define SYSCFG_BASEADDR			(APB2PERIPH_BASEADDR +0x3800U)
#define USART1_BASEADDR			(APB2PERIPH_BASEADDR +0x1000U)
#define EXTI_BASEADDR			(APB2PERIPH_BASEADDR +0x3C00U)

// Base address of peripherals which hanging on APB2
#define PWR_BASEADDR		 	(APB1PERIPH_BASEADDR+ 0x7000U)
//-----------------*****-----------AHB1----------------*****------------//
// define struct of GPIO

typedef struct
{
	__vo uint32_t	MODER;		//GPIO port mode register 				Address offset: 0x00
	__vo uint32_t	OTYPER; 	//GPIO port output type register 		Address offset: 0x04
	__vo uint32_t	OSPEEDR; 	//GPIO port output speed register 		Address offset: 0x08
	__vo uint32_t	PUPDR; 		//GPIO port pull-up/pull-down register 	Address offset: 0x0C
	__vo uint32_t	IDR; 		//GPIO port input data register 		Address offset: 0x10
	__vo uint32_t	ODR; 		//GPIO port output data register 		Address offset: 0x14
	__vo uint32_t	BSRR; 		//GPIO port bit set/reset register 		Address offset: 0x18
	__vo uint32_t	LCKR; 		//GPIO port configuration lock register Address offset: 0x1C
	__vo uint32_t	AFR[2]; 		//GPIO alternate function low register 	Address offset: 0x20
}GPIO_RgDef_t; //possible value @GPIO Definition


//	define struct of RCC
typedef struct
{
	__vo uint32_t	CR; //RCC clock control register 						Address offset: 0x00
	__vo uint32_t	PLLCFGR; //RCC PLL configuration register 				Address offset: 0x04
	__vo uint32_t	CFGR; //RCC clock configuration register 				Address offset: 0x08
	__vo uint32_t	CIR; //RCC clock interrupt register 					Address offset: 0x0C
	__vo uint32_t	AHB1RSTR; //RCC AHB1 peripheral reset register 			Address offset: 0x10
	__vo uint32_t	AHB2RSTR; //RCC AHB2 peripheral reset register 			Address offset: 0x14
	__vo uint32_t	RESERVED1[2];										//	0x18,0x1C
	__vo uint32_t	APB1RSTR; //RCC APB1 peripheral reset register 			Address offset: 0x20
	__vo uint32_t	APB2RSTR; //RCC APB2 peripheral reset register 			Address offset: 0x24
	__vo uint32_t	RESERVED2[2];										//	0x28,0x2C
	__vo uint32_t	AHB1ENR; //RCC AHB1 peripheral clock enable register 	Address offset: 0x30
	__vo uint32_t	AHB2ENR; //RCC AHB2 peripheral clock enable register 	Address offset: 0x34
	__vo uint32_t	RESERVED3[2];										//	0x38,0x3C
	__vo uint32_t	APB1ENR; //RCC APB1 peripheral clock enable register 	Address offset: 0x40
	__vo uint32_t	APB2ENR; //RCC APB2 peripheral clock enable register 	Address offset: 0x44
	__vo uint32_t	RESERVED4[2];										//	0x48,0x4C
	__vo uint32_t	AHB1LPENR; //RCC AHB1 peripheral clock enable register 	Address offset: 0x50
	__vo uint32_t	AHB2LPENR; //RCC AHB1 peripheral clock enable register 	Address offset: 0x54
	__vo uint32_t	RESERVED5[2];										//	0x58,0x5C
	__vo uint32_t	APB1LPENR; //RCC AHB1 peripheral clock enable register 	Address offset: 0x60
	__vo uint32_t	APB2LPENR; //RCC clock control register 				Address offset: 0x64
	__vo uint32_t	RESERVED6[2];										//	0x68,0x6C
	__vo uint32_t	BDCR; //RCC clock control register 						Address offset: 0x70
	__vo uint32_t	CSR; //RCC clock control register 						Address offset: 0x74
	__vo uint32_t	RESERVED7[2];										//	0x78,0x7C
	__vo uint32_t	SSCGR; //RCC clock control register 					Address offset: 0x80
	__vo uint32_t	PLLI2SCFGR; //RCC PLLI2S configuration register  		Address offset: 0x84
	__vo uint32_t	RESERVED8;										//	0x88
	__vo uint32_t	DCKCFGR; //RCC Dedicated Clocks Configuration Register 	Address offset: 0x8C
}RCC_RgDef_t; //possible value @RCC Definition

//define struct of PWR
typedef struct
{
	__vo uint32_t CR;
	__vo uint32_t CSR;
}PWR_RgDef_t; //possible value @PWR Definition

//define struct of FLASH_R
typedef struct
{
	  __vo uint32_t ACR;      /*!< FLASH access control register,   Address offset: 0x00 */
	  __vo uint32_t KEYR;     /*!< FLASH key register,              Address offset: 0x04 */
	  __vo uint32_t OPTKEYR;  /*!< FLASH option key register,       Address offset: 0x08 */
	  __vo uint32_t SR;       /*!< FLASH status register,           Address offset: 0x0C */
	  __vo uint32_t CR;       /*!< FLASH control register,          Address offset: 0x10 */
	  __vo uint32_t OPTCR;    /*!< FLASH option control register ,  Address offset: 0x14 */
	  __vo uint32_t OPTCR1;   /*!< FLASH option control register 1, Address offset: 0x18 */
}FLASH_RgDef_t;

//define struct of EXTI
typedef struct
{
	__vo uint32_t IMR;	//Interrupt mask register 				Address offset: 0x00
	__vo uint32_t EMR;	//Event  mask register 					Address offset: 0x04
	__vo uint32_t RTSR;	//Rising trigger selection register 	Address offset: 0x08
	__vo uint32_t FTSR;	//Falling trigger selection register 	Address offset: 0x0C
	__vo uint32_t SWIER;//Software interrupt event register 	Address offset: 0x10
	__vo uint32_t PR;	//Pending register 						Address offset: 0x14
}EXTI_RgDef_t;

//define struct of SYSCFG
typedef struct
{
	__vo uint32_t MEMRMP;       /*!< SYSCFG memory remap register,                      Address offset: 0x00      */
	__vo uint32_t PMC;          /*!< SYSCFG peripheral mode configuration register,     Address offset: 0x04      */
	__vo uint32_t EXTICR[4];    /*!< SYSCFG external interrupt configuration registers, Address offset: 0x08-0x14 */
  uint32_t      RESERVED[2];  	/*!< Reserved, 0x18-0x1C                                                          */
    __vo uint32_t CMPCR;        /*!< SYSCFG Compensation cell control register,         Address offset: 0x20      */
}SYSCFG_RgDef_t;

//define struct of TIM
typedef struct
{
	  __vo uint32_t CR1;         /*!< TIM control register 1,              Address offset: 0x00 */
	  __vo uint32_t CR2;         /*!< TIM control register 2,              Address offset: 0x04 */
	  __vo uint32_t SMCR;        /*!< TIM slave mode control register,     Address offset: 0x08 */
	  __vo uint32_t DIER;        /*!< TIM DMA/interrupt enable register,   Address offset: 0x0C */
	  __vo uint32_t SR;          /*!< TIM status register,                 Address offset: 0x10 */
	  __vo uint32_t EGR;         /*!< TIM event generation register,       Address offset: 0x14 */
	  __vo uint32_t CCMR1;       /*!< TIM capture/compare mode register 1, Address offset: 0x18 */
	  __vo uint32_t CCMR2;       /*!< TIM capture/compare mode register 2, Address offset: 0x1C */
	  __vo uint32_t CCER;        /*!< TIM capture/compare enable register, Address offset: 0x20 */
	  __vo uint32_t CNT;         /*!< TIM counter register,                Address offset: 0x24 */
	  __vo uint32_t PSC;         /*!< TIM prescaler,                       Address offset: 0x28 */
	  __vo uint32_t ARR;         /*!< TIM auto-reload register,            Address offset: 0x2C */
	  __vo uint32_t RCR;         /*!< TIM repetition counter register,     Address offset: 0x30 */
	  __vo uint32_t CCR1;        /*!< TIM capture/compare register 1,      Address offset: 0x34 */
	  __vo uint32_t CCR2;        /*!< TIM capture/compare register 2,      Address offset: 0x38 */
	  __vo uint32_t CCR3;        /*!< TIM capture/compare register 3,      Address offset: 0x3C */
	  __vo uint32_t CCR4;        /*!< TIM capture/compare register 4,      Address offset: 0x40 */
	  __vo uint32_t BDTR;        /*!< TIM break and dead-time register,    Address offset: 0x44 */
	  __vo uint32_t DCR;         /*!< TIM DMA control register,            Address offset: 0x48 */
	  __vo uint32_t DMAR;        /*!< TIM DMA address for full transfer,   Address offset: 0x4C */
	  __vo uint32_t OR;          /*!< TIM option register,                 Address offset: 0x50 */
}TIM_RgDef_t;

//define struct of USART
typedef struct
{
	__vo uint32_t SR;
	__vo uint32_t DR;
	__vo uint32_t BRR;
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t CR3;
	__vo uint32_t GTPR;

}USART_RgDef_t;
//------------------------------------------------------------------//
//@GPIO Definition
//peripheral GPIO definition
#define GPIOA				((GPIO_RgDef_t*)GPIOA_BASEADDR)
#define GPIOB				((GPIO_RgDef_t*)GPIOB_BASEADDR)
#define GPIOC				((GPIO_RgDef_t*)GPIOC_BASEADDR)
#define GPIOD				((GPIO_RgDef_t*)GPIOD_BASEADDR)
#define GPIOE				((GPIO_RgDef_t*)GPIOE_BASEADDR)
#define GPIOH				((GPIO_RgDef_t*)GPIOH_BASEADDR)

//@RCC Definition
//peripheral RCC definition
#define RCC			((RCC_RgDef_t*)RCC_BASEADDR)

//@PWC Definition
#define PWR 		((PWR_RgDef_t*)PWR_BASEADDR)

//@FLASH Definition
#define FLASH		((FLASH_RgDef_t*)FLASH_R_BASEADDR)

//@EXTI Definition
#define EXTI		((EXTI_RgDef_t*)EXTI_BASEADDR)

//@SYSCFG Definition
#define SYSCFG		((SYSCFG_RgDef_t*)SYSCFG_BASEADDR)

//@TIM Definition
#define TIM2		((TIM_RgDef_t*)TIM2_BASEADDR)

//@USART Definition
#define USART1		((USART_RgDef_t*)USART1_BASEADDR)
#define USART2		((USART_RgDef_t*)USART2_BASEADDR)
//-------------------------MACRO FUNTION---------------------------//
//clock enable macros for GPIOx peripheral
#define GPIOA_PCLK_EN()		(RCC->AHB1ENR|=(1<<0))
#define GPIOB_PCLK_EN()		(RCC->AHB1ENR|=(1<<1))
#define GPIOC_PCLK_EN()		(RCC->AHB1ENR|=(1<<2))
#define GPIOD_PCLK_EN()		(RCC->AHB1ENR|=(1<<3))
#define GPIOE_PCLK_EN()		(RCC->AHB1ENR|=(1<<4))
#define GPIOH_PCLK_EN()		(RCC->AHB1ENR|=(1<<7))

// clock disable macros for GPIOx peripheral
#define GPIOA_PCLK_DIS()	(RCC->AHB1ENR&=~(1<<0))
#define GPIOB_PCLK_DIS()	(RCC->AHB1ENR&=~(1<<1))
#define GPIOC_PCLK_DIS()	(RCC->AHB1ENR&=~(1<<2))
#define GPIOD_PCLK_DIS()	(RCC->AHB1ENR&=~(1<<3))
#define GPIOE_PCLK_DIS()	(RCC->AHB1ENR&=~(1<<4))
#define GPIOH_PCLK_DIS()	(RCC->AHB1ENR&=~(1<<7))

// reset GPIOx peripheral
#define GPIOA_REG_RESET()	do{RCC->AHB1RSTR|=(1<<0);RCC->AHB1RSTR&=~(1<<0);}while(0)
#define GPIOB_REG_RESET()	do{RCC->AHB1RSTR|=(1<<1);RCC->AHB1RSTR&=~(1<<1);}while(0)
#define GPIOC_REG_RESET()	do{RCC->AHB1RSTR|=(1<<2);RCC->AHB1RSTR&=~(1<<2);}while(0)
#define GPIOD_REG_RESET()	do{RCC->AHB1RSTR|=(1<<3);RCC->AHB1RSTR&=~(1<<3);}while(0)
#define GPIOE_REG_RESET()	do{RCC->AHB1RSTR|=(1<<4);RCC->AHB1RSTR&=~(1<<4);}while(0)
#define GPIOH_REG_RESET()	do{RCC->AHB1RSTR|=(1<<7);RCC->AHB1RSTR&=~(1<<7);}while(0)

//clock enable macros for SYSCFG exti
#define SYSCFG_PCLK_EN()	(RCC->APB2ENR|=(1<<14))

//clock disable macros for SYSCFG exti
#define SYSCFG_PCLK_DIS()	(RCC->APB2ENR&=~(1<<14))

//clock enable macros for TIM
#define TIM2_PCLK_EN()		(RCC->APB1ENR|=(1<<0))

//clock disable macros for TIM
#define TIM2_PCLK_DIS()		(RCC->APB1ENR&=~(1<<0))

//reset timer
#define TIM2_REG_RESET()	do{RCC->APB1RSTR|=(1<<0);RCC->APB1RSTR&=~(1<<0);}while(0)

//clock enable macros for USART
#define USART1_PCLK_EN()	(RCC->APB2ENR)|=(1<<4)
#define USART2_PCLK_EN()	(RCC->APB1ENR)|=(1<<17)
//clock disable macros for USART
#define USART1_PCLK_DIS()	(RCC->APB2ENR)&=~(1<<4)
#define USART2_PCLK_DIS()	(RCC->APB1ENR)&=~(1<<17)
#endif /* INC_STM32F411_H_ */
