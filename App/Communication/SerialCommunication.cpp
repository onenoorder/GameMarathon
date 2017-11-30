/* 
* SerialCommunication.cpp
*
* Created: 30-11-2017 10:21:16
* Author: Gerhard
*/


#include "SerialCommunication.h"

// default constructor
SerialCommunication::SerialCommunication()
{
} //SerielCommunication

void SerialCommunication::Begin(){
	Serial.begin(9600);
}

void SerialCommunication::Send(unsigned char data){
	Serial.write(data);
}

unsigned char SerialCommunication::Receive(){
	while(!Serial.available());
	return Serial.read();
}

// default destructor
SerialCommunication::~SerialCommunication()
{
} //~SerielCommunication
