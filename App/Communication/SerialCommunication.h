/* 
* SerialCommunication.h
*
* Created: 30-11-2017 10:21:16
* Author: Gerhard
*/

#ifndef __SERIALCOMMUNICATION_H__
#define __SERIALCOMMUNICATION_H__

#include "Communication.h"
#include "Arduino.h"

class SerialCommunication : public Communication
{
//variables
public:
protected:
private:

//functions
public:
	SerialCommunication();
	virtual void Begin();
	virtual void Send(unsigned char data);
	virtual unsigned char Receive();
	~SerialCommunication();
protected:
private:

}; //SerialCommunication

#endif //__SERIALCOMMUNICATION_H__
