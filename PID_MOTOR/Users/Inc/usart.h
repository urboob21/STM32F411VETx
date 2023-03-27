/*
 * usart.h
 *
 *  Created on: Mar 22, 2023
 *      Author: Phong Nguyen
 */

#ifndef INC_USART_H_
#define INC_USART_H_
#include "main.h"
#include <stdlib.h>
#include <stdbool.h>

#define  DATASIZE 21

typedef enum
{
  NONE = 1,
  SPID,
  CTUN,
  GPID
} StateProcess_t;


void UsartReceiveIT(void);
bool StrCompare(uint8_t *pBuff, uint8_t *pSample, uint8_t nSize);
void UsartWriteComm(uint8_t *pData);
void UsartReadComm(uint8_t *nRxData,bool *r_DataAvailable);
void MX_USART2_UART_Init(void);


#endif /* INC_USART_H_ */
