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

void Master::SendTo(int ID){
	Wire.beginTransmission(ID);
	Wire.write(OutputData);
	Wire.endTransmission();
}

void Master::ReceiveFrom(int ID){
	Wire.requestFrom(ID, 1);

	while (Wire.available()) {
		InputData = Wire.read();
	}
}

// default destructor
Master::~Master()
{
} //~Master
