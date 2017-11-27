/*
 * Data.h
 *
 * Created: 20-11-2017 15:57:29
 *  Author: Gerhard
 */ 
#ifndef __DATA_H__
#define __DATA_H__

#include <Wire.h>

extern unsigned char InputData;
extern unsigned char OutputData;
extern unsigned char ReceivedData;

void ReceiveData(int count);
void RequestData(int count);

#endif //__DATA_H__