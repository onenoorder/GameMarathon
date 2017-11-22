/*
 * Data.cpp
 *
 * Created: 20-11-2017 16:31:37
 *  Author: Gerhard
 */ 
#include "Data.h"

unsigned char InputData = 0;
unsigned char OutputData = 0;

void ReceiveData(int count) {
	while (Wire.available() > 0) {
		InputData = Wire.read();
	}
}

void RequestData(int count) {
	Wire.write(OutputData);
}