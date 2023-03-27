/* INCLUDE LIB*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "clock.h"
#include "pid.h"
#include "mylib.h"
#include "motor.h"

#define SETPOINT 125

/*---------- SYSTEM VAR ----------*/
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_tx;

/*---------- UART VAR ----------*/
extern uint8_t uCommand[4];
extern uint8_t uOption[3];
extern uint8_t uData[12];
extern bool uDataAvailable;
StateProcess_t stateProcess =NONE;

/*---------- PID VAR ----------*/
extern PIDControl_t PIDControl;

/*---------- MOTOR VAR ----------*/
extern uint16_t g_mIndex;
extern uint16_t g_mCmdPulse;
//
uint8_t tunData[400];


int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MotorInit();
  UsartReceiveIT();
  while (1)
  {
	  /*---------- convert CMD to STATE PROCESS  ----------*/
	  if(uDataAvailable)
	  {
		  if(StrCompare(uCommand,(uint8_t*)"SPID",4))
		  	  	  stateProcess =SPID;
		  else if(StrCompare(uCommand,(uint8_t*)"CTUN",4))
			  	  stateProcess=CTUN;
		  else if(StrCompare(uCommand,(uint8_t*)"GPID",4))
			  	  stateProcess=GPID;
		  uDataAvailable=false;
	  }

	  /*---------- STATE PROCESS handle ----------*/
	  switch(stateProcess)
	  {
	  case NONE:
		  UsartReceiveIT();
		  break;

	  case SPID:
		  //reset
		  g_mIndex = 0;
		  g_mCmdPulse = 0;
		  PIDReset(&PIDControl);
		  //reset encoder
		  __HAL_TIM_SetCounter(&htim4, 32768);
		  //get kp,ki,kd
		  PIDControl.pKp=get_PIDdata(uData,1);
		  PIDControl.pKi=get_PIDdata(uData,2);
		  PIDControl.pKd=get_PIDdata(uData,3);
		  stateProcess=NONE;
		  break;

	  case CTUN:
		  break;
	  case GPID:
		  //uint16t value position -> uint8t[2]
		  for(int i=0;i<200;i++)
		  {
			  uint8_t reg_data[2];
		  	  reg_data[0]=((PIDControl.pSampleTuningPID[i]&0xFF00)>>8);
		  	  reg_data[1]=(PIDControl.pSampleTuningPID[i]&0xFF);
		  	  tunData[2*i]=reg_data[0];
		  	  tunData[2*i+1]=reg_data[1];
		  }
		  HAL_UART_Transmit_DMA(&huart2,tunData,400);
		  uDataAvailable=false;
		  stateProcess=NONE;
		  break;
	  }
  }
}


/*---------- Interrupt process ----------*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == htim2.Instance)
  {
	  switch(stateProcess)
	  {
	  case NONE:
		  break;
	  case CTUN:
			if (g_mIndex <= 200)
			{
				MotorTuning(SETPOINT);
			}

			else
			{
				MotorStop();
				stateProcess = NONE;
			}
	  }

  }
}










void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
