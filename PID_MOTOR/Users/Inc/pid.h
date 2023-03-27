/*
 * pid.h
 *
 *  Created on: Mar 22, 2023
 *      Author: Phong Nguyen
 */

#ifndef INC_PID_H_
#define INC_PID_H_
#include "main.h"
#include <stdint.h>

typedef struct {
	float pKp, pKi, pKd;
	float pErrorTerm;
	float pIntergral;
	uint16_t pSampleTuningPID[200];
	uint16_t pActPosSample[1000];
} PIDControl_t;

void PIDReset(PIDControl_t *pPIDControl);
void PIDInit(PIDControl_t *pPIDControl, float pKp, float pKi, float pKd);
void PIDTuningSet(PIDControl_t *pPIDControl, float pKp, float pKi, float pKd);
float PIDCompute(PIDControl_t *pPIDControl, float pCmdValue, float pActValue, float pTs);


#endif /* INC_PID_H_ */
