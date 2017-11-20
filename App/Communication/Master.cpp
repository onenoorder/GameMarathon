/* 
* Master.cpp
*
* Created: 14-11-2017 13:54:38
* Author: Gerhard
*/


#include "Master.h"

// default constructor
Master::Master()
{
	Wire.begin();
} //Master

void Master::Update(){
	Wire.beginTransmission(1);
	Wire.write(OutputData);
	Wire.endTransmission();
	
	OutputData = 0;

	Wire.requestFrom(1, 1);

	while (Wire.available()) {
		InputData = Wire.read();
	}
}

// default destructor
Master::~Master()
{
} //~Master
