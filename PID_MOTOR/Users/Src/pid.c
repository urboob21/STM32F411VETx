/*
 * pid.c
 *
 *  Created on: Mar 22, 2023
 *      Author: Phong Nguyen
 */

#include "pid.h"
#include "main.h"
#include "tim.h"
extern TIM_HandleTypeDef htim4;
float pPIDError = 0;
PIDControl_t PIDControl;

//reset error,interral te
void PIDReset(PIDControl_t *pPIDControl){
	pPIDError=0;
	PIDControl.pErrorTerm=0;
	PIDControl.pIntergral=0;
}

void PIDInit(PIDControl_t *pPIDControl, float pKp, float pKi, float pKd)
{
	PIDReset(pPIDControl);
	pPIDControl->pKp = pKp;
	pPIDControl->pKi = pKi;
	pPIDControl->pKd = pKp;
	__HAL_TIM_SetCounter(&htim4,32768);  //gia tri dem ban dau la 32768 ?
}

void PIDTuningSet(PIDControl_t *pPIDControl, float pKp, float pKi, float pKd)
{
  if(pKp < 0.0f || pKi < 0.0f || pKp < 0.0f)
  {
      return;
  }
  pPIDControl->pKp = pKp;
  pPIDControl->pKi = pKi;
  pPIDControl->pKd = pKd;
}


float PIDCompute(PIDControl_t *pPIDControl, float pCmdValue, float pActValue, float pTs)
{
	float pPIDResult;
	pPIDError = pCmdValue - pActValue;
	float dP = 0, dI = 0, dD = 0;

	dP = pPIDControl->pKp * pPIDError;
	pPIDControl->pIntergral += pPIDError;
	dI = pPIDControl->pKi * pTs / 2 * pPIDControl->pIntergral;
	dD = pPIDControl->pKd * (pPIDError - pPIDControl->pErrorTerm) / pTs;
	pPIDResult = dP + dI + dD;
	pPIDControl->pErrorTerm = pPIDError;

	return pPIDResult;
}
