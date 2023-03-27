/*
 * usart.c
 *
 *  Created on: Mar 22, 2023
 *      Author: Phong Nguyen
 */
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "usart.h"

extern UART_HandleTypeDef huart2;
uint8_t uRxBuff[DATASIZE];
uint8_t uCommand[4];
uint8_t uOption[3];
uint8_t uData[12];
bool uDataAvailable = false;

uint8_t STX[] = {0x02U};
uint8_t ETX[] = {0x03U};


/*Interrupt Rx Callback
 *
 *
 *
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == huart2.Instance)
    {

    	UsartReadComm(uRxBuff,&uDataAvailable);
    }
}

/*Interrupt Tx Callback
 *
 *
 *
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == huart2.Instance)
    {

    }
}

/*Compare two buff
 *
 *
 *
 */
bool StrCompare(uint8_t *pBuff, uint8_t *pSample, uint8_t nSize)
{
    for (int i = 0; i < nSize; i++)
    {
        if (pBuff[i] != pSample[i])
        {
            return false;
        }
    }
    return true;
}

/*Enable Interrupt Received
 *
 *
 *
 */
void UsartReceiveIT(void)
{
    HAL_UART_Receive_IT(&huart2, (uint8_t *)uRxBuff, DATASIZE);
}


void UsartWriteComm(uint8_t *pData)
{
	uint8_t pBuff[402];
    uint8_t nIndex = 0;
//    memcpy(pBuff+nIndex,STX,1);
//    nIndex += 1;
//    memcpy(pBuff+nIndex,pData,400);
//    nIndex += 400;
//    memcpy(pBuff+nIndex,ETX,1);
    pBuff[0]=STX[0];
    pBuff[401]=ETX[0];
    for(int i=0;i<400;i++)
    {
    	pBuff[i+1]=pData[i];
    }

		HAL_UART_Transmit_DMA(&huart2,pBuff,402);


}

/*Process Data read
 *
 *
 *
 */
void UsartReadComm(uint8_t *nRxData,bool *r_DataAvailable)
{
	if ((nRxData[0] == STX[0]) && (nRxData[DATASIZE-1] == ETX[0]))
    {
			 memcpy(uCommand,nRxData+1,4);
			 memcpy(uOption,nRxData+5,3);
			 memcpy(uData,nRxData+8,12);
				*r_DataAvailable=true;
		}
			else *r_DataAvailable=false;
}

void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}
