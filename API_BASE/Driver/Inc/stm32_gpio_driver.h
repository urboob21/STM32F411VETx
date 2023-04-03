/*
 * stm32_gpio_driver.h
 *
 *  Created on: Feb 25, 2023
 *      Author: Phong Nguyen
 */

#ifndef INC_STM32_GPIO_DRIVER_H_
#define INC_STM32_GPIO_DRIVER_H_
#include "stm32f411.h"
typedef struct
{
	uint8_t GPIO_PIN;				//possible values from @GPIO_PIN_NUMBER
	uint8_t GPIO_MODE;				//possible values from @GPIO_PIN_MODE
	uint8_t GPIO_SPEED;				//possible values from @GPIO_PIN_SPEED
	uint8_t GPIO_ITYPE;				//possible values from @GPIO_PIN_IP_TYPE
	uint8_t GPIO_OTYPE;			//possible values from @GPIO_PIN_OP_TYPE
	uint8_t GPIO_ALTF;			//possible values from @GPIO_PIN_Altfunmode
}GPIO_PinConfig_t;

typedef struct
{
	GPIO_RgDef_t *pGPIOx; //pointer hold address GPIO port which the pin belong
	GPIO_PinConfig_t GPIO_PinConfig;
}GPIO_Handle_t;

//@GPIO_PIN_NUMBER
#define GPIO_PIN_0 			0
#define GPIO_PIN_1 			1
#define GPIO_PIN_2 			2
#define GPIO_PIN_3 			3
#define GPIO_PIN_4 			4
#define GPIO_PIN_5 			5
#define GPIO_PIN_6 			6
#define GPIO_PIN_7 			7
#define GPIO_PIN_8 			8
#define GPIO_PIN_9 			9
#define GPIO_PIN_10 		10
#define GPIO_PIN_11			11
#define GPIO_PIN_12 		12
#define GPIO_PIN_13 		13
#define GPIO_PIN_14 		14
#define GPIO_PIN_15 		15

//@GPIO_PIN_MODE
#define GPIO_MODE_IN 				0
#define GPIO_MODE_OUT 				1
#define GPIO_MODE_ALTFN 			2
#define GPIO_MODE_ANALOG 			3
#define GPIO_MODE_IT_FT				4
#define GPIO_MODE_IT_RT				5
#define GPIO_MODE_IT_RFT			6

//@GPIO_PIN_SPEED
#define GPIO_SPEED_LOW 		0
#define GPIO_SPEED_MEDIUM	1
#define GPIO_SPEED_FAST 	2
#define GPIO_SPEED_HIGH 	3

//@GPIO_PIN_IP_TYPE
#define GPIO_ITYPE_NO			0
#define GPIO_ITYPE_PU			1
#define GPIO_ITYPE_PD			2

//@GPIO_PIN_OP_TYPE
#define GPIO_OTYPE_PP		0
#define GPIO_OTYPE_OD		1

//@GPIO_ALTF_TYPE
#define GPIO_ALTF_AF0			0
#define GPIO_ALTF_AF1			1
#define GPIO_ALTF_AF2			2
#define GPIO_ALTF_AF3			3
#define GPIO_ALTF_AF4			4
#define GPIO_ALTF_AF5			5
#define GPIO_ALTF_AF6			6
#define GPIO_ALTF_AF7			7
#define GPIO_ALTF_AF8			8
#define GPIO_ALTF_AF9			9
#define GPIO_ALTF_AF10			10
#define GPIO_ALTF_AF11			11
#define GPIO_ALTF_AF12			12
#define GPIO_ALTF_AF13			13
#define GPIO_ALTF_AF14			14
#define GPIO_ALTF_AF15			15


//peripheral clock  settup
void GPIO_PeriClockControl(GPIO_RgDef_t *pGPIOx,uint8_t EnorDi);

//init and de-init
void GPIO_Init(GPIO_Handle_t	*pGIPOHandle);
void GPIO_DeInit(GPIO_RgDef_t *pGPIOx);

//Data read and write
uint8_t GPIO_ReadFromInputPin(GPIO_RgDef_t *pGPIOx,uint8_t GPIO_PIN);
uint16_t GPIO_ReadFromInputPort(GPIO_RgDef_t *pGPIOx);
void GPIO_WritetoOutPin(GPIO_RgDef_t *pGPIOx,uint8_t GPIO_PIN,uint8_t value);
void GPIO_WritetoOutPort(GPIO_RgDef_t *pGPIOx,uint8_t value);
void GPIO_ToggleOutputPin(GPIO_RgDef_t *pGPIOx,uint8_t GPIO_PIN);

//IRQ config and IRQ handling
void GPIO_IRQConfig(void);
void GPIO_IRQHandling(void);


#endif /* INC_STM32_GPIO_DRIVER_H_ */
