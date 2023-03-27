/*
 * motor.h
 *
 *  Created on: Mar 22, 2023
 *      Author: Phong Nguyen
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_
#include "main.h"
 void MotorSetDuty(int32_t mDuty);
 void MotorInit(void);
 uint16_t ConvertDegToPulse(uint16_t mDeg);
 uint16_t ConvertPulseToDeg(uint16_t mPulse);
 void MotorGetPulse(uint16_t *mPulse);
 void MotorTuning(uint16_t mPos);
 void MotorStop();

#endif /* INC_MOTOR_H_ */
