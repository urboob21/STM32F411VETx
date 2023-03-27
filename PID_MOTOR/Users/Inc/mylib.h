/*
 * mylib.h
 *
 *  Created on: Mar 22, 2023
 *      Author: Phong Nguyen
 */

#ifndef INC_MYLIB_H_
#define INC_MYLIB_H_
#include "main.h"

#include <stdint.h>
#include <math.h>
#include <string.h>
float a4utofloat(uint8_t* avalue)
{
	float temp;

	temp=avalue[0]*10.+avalue[1]+avalue[2]/100.+avalue[3]/1000.;


	return temp;
}
float get_PIDdata(uint8_t* value,int index)
{
	float temp;
	uint8_t index_value[4];
	if(index==1)
		memcpy(index_value,value+0,4);
	else if(index==2)
		memcpy(index_value,value+4,4);
	else if(index==3)
		memcpy(index_value,value+8,4);
	temp=a4utofloat(index_value);
	return temp;
}
void float2Ints(float value, uint8_t* r_data)
{ //999.999
    r_data[0]=(uint8_t)(value/10); //r[0]=99
    r_data[1]=(uint8_t)(value-r_data[0]*10); //r[1]=9
    r_data[2]=(uint8_t)((value-(uint8_t)value)*100); //.99
    r_data[3]=(uint8_t)((value-(uint8_t)value)*1000)-r_data[2]*10;
}

#endif /* INC_MYLIB_H_ */
