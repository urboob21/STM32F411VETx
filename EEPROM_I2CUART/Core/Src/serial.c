#include "serial.h"
extern UART_HandleTypeDef huart2;
uint8_t RxData[10];
uint8_t TxData[514]; 
uint8_t r_cmd[1];
uint8_t r_address[2];
uint8_t r_data[5];
bool r_DataAvailable = false;
extern uint16_t address;
extern uint8_t dem;
uint8_t STX[] = {0x02U};
uint8_t ETX[] = {0x03U};

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


void Writecomm(uint8_t *pBuff, uint8_t nSize)
{
	HAL_UART_Transmit_DMA(&huart2,pBuff,nSize);
}

void Readcomm(uint8_t *nRxData,uint8_t nSize,bool *r_DataAvailable)
{
	if ((nRxData[0] == STX[0]) && (nRxData[9] == ETX[0]))
    {
      // memcpy(r_cmd,subString(nRxData, 1, 4), 4); 
      // memcpy(r_address,subString(nRxData, 5, 3), 3);
      // memcpy(r_data, subString(nRxData, 8, 8), 8);
			// cat data thanh tung byte , 1byte , 2byte, 6 byte
			 memcpy(r_cmd,nRxData+1,1); 
       memcpy(r_address,nRxData+2,2);
       memcpy(r_data,nRxData+4,5);
			address=((uint16_t)r_address[1]<<8|r_address[0]);
				*r_DataAvailable=true;
		}
	 else *r_DataAvailable=false;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == huart2.Instance)
    {
      Readcomm(RxData,10,&r_DataAvailable);
      HAL_UART_Receive_DMA(&huart2,RxData,10);
			//HAL_UART_Transmit_DMA(&huart2,dataxx,514);
		//	HAL_UART_Receive_DMA(&huart2,RxData,10);
    }
}