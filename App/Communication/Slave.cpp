/* 
* Slave.cpp
*
* Created: 14-11-2017 13:54:24
* Author: Gerhard
*/


#include "Slave.h"

// default constructor
Slave::Slave(unsigned char ID)
{
	this->ID = ID;
	Wire.begin(ID);
	Wire.onReceive(ReceiveData);
	Wire.onRequest(RequestData);
} //Slave

// default destructor
Slave::~Slave()
{
} //~Slave
