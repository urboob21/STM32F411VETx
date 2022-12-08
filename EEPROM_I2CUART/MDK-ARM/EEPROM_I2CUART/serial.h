#ifndef _SERIAL_H
#define _SERIAL_H
/* PC->ARM: receive -> Check stx,etx  -> tach -> ghep -> send 
  *|STX	|CMD 	|ADDRESS|			Data 6		 	|ETX| 	
  *|02	|xx		|xx | xx|xx|xx|xx|xx|xx|xx| 03| */
//--------------------KHAI BAO THU VIEN
#include "main.h"	
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//--------------------KHAI BAO CAC BIEN MARCO
//--------------------KHAI BAO CAC HAM
	
uint8_t *subString(uint8_t *pBuff, int nPos, int nIndex);
bool StrCompare(uint8_t *pBuff, uint8_t *pSample, uint8_t nSize);
void Readcomm(uint8_t *pBuff,uint8_t nSize,bool *g_bDataAvailable);
void Writecomm(uint8_t *pBuff,uint8_t nSize);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);














#endif