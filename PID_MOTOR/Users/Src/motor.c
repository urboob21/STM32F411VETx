/*
 * motor.c
 *
 *  Created on: Mar 22, 2023
 *      Author: Phong Nguyen
 */
#include "motor.h"
#include "pid.h"
#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "usart.h"

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;

//PID var
extern PIDControl_t PIDControl;

//
uint16_t Duty[200];
int32_t g_mDutyCycle;
float g_mCmdVel;
uint16_t g_mActPulse;
uint16_t g_mCmdPulse;
uint16_t g_mIndex = 0;

void MotorInit(void)
{
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_2);

	PIDReset(&PIDControl);
	PIDInit(&PIDControl, 1., 0., 0.00);
}

void MotorTuning(uint16_t mPos)
{
	uint16_t mPulse;
	MotorGetPulse(&mPulse);

	//get actual value           0       b       2^15: count up or downd -> set
	if(mPulse>=32768)
	g_mActPulse = mPulse - 32768;
	else if(mPulse<32768)
	g_mActPulse=32768-mPulse;

	//

	g_mCmdPulse = ConvertDegToPulse(mPos);
	g_mDutyCycle = (int32_t)PIDCompute(&PIDControl, g_mCmdPulse, g_mActPulse, 0.01f);
	MotorSetDuty(g_mDutyCycle);
	// Store data -> 100mau gui 1 lan
	PIDControl.pSampleTuningPID[g_mIndex] = ConvertPulseToDeg(g_mActPulse);
	g_mIndex++;
}



void MotorStop(){
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);
}

void MotorSetDuty(int32_t nDuty)
{
	if (nDuty >= 0)
	{
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, abs(nDuty));
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);
	}
	else if (g_mDutyCycle < 0)
	{
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, abs(nDuty));  //xuat PWM
	}
}

uint16_t ConvertDegToPulse(uint16_t mDeg)
{
	float mPulse = mDeg * 7392 / 360;

	return (uint16_t)mPulse;
}

uint16_t ConvertPulseToDeg(uint16_t mPulse)
{
	float mDeg = mPulse * 360 / 7392 ;
	return (uint16_t)mDeg;
}

void MotorGetPulse(uint16_t *mPulse)
{
	*mPulse = __HAL_TIM_GetCounter(&htim4);
}



