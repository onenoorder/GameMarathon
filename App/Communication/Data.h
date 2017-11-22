/*
 * Data.h
 *
 * Created: 20-11-2017 15:57:29
 *  Author: Gerhard
 */ 
#include <Wire.h>

#ifndef __DATA_H__
#define __DATA_H__

extern unsigned char InputData;
extern unsigned char OutputData;

void ReceiveData(int count);
void RequestData(int count);

#endif //__DATA_H__