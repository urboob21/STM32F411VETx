/*
 * core.h
 *
 *  Created on: Feb 26, 2023
 *      Author: Phong Nguyen
 */

#ifndef INC_CORE_H_
#define INC_CORE_H_
#include <stdint.h>

#define __IOM volatile
/* Memory mapping of Core Hardware */
#define SCS_BASEADDR            (0xE000E000UL)
#define SYSTICK_BASEADDR		(SCS_BASEADDR +  0x0010UL)
#define NVIC_BASEADDR           (SCS_BASEADDR +  0x0100UL)


//define struct of NVIC
typedef struct
{
  __IOM uint32_t ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
        uint32_t RESERVED0[24U];
  __IOM uint32_t ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
        uint32_t RESERVED1[24U];
  __IOM uint32_t ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
        uint32_t RESERVED2[24U];
  __IOM uint32_t ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
        uint32_t RESERVED3[24U];
  __IOM uint32_t IABR[8U];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
        uint32_t RESERVED4[56U];
  __IOM uint8_t  IP[240U];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
        uint32_t RESERVED5[644U];
  __IOM  uint32_t STIR;                   /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
}  NVIC_RegDef_t;

//define struct of SYSTICK
typedef struct
{
  __IOM uint32_t CSR;                   /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  __IOM uint32_t RVR;                   /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
  __IOM uint32_t CVR;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
  __IOM  uint32_t CALIB;                  /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} SYSTICK_RegDef_t;


//@NIC Definition
#define NVIC	((NVIC_RegDef_t*)NVIC_BASEADDR)

//@SYSTICK Definition
#define SYSTICK ((SYSTICK_RegDef_t*)SYSTICK_BASEADDR)

#endif /* INC_CORE_H_ */
