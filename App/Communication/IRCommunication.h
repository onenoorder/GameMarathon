/* 
* IRCommunication.h
*
* Created: 13-12-2017 14:04:35
* Author: Mikena
*/

#ifndef __IRCOMMUNICATION_H__
#define __IRCOMMUNICATION_H__

#include "Communication.h"
#include "Arduino.h"

class IRCommunication: public Communication
{
//variables
public:
	int KHZ = 38;
	int Counter = 0;
	int SubCounter = 0;
protected:
private:
	char _sendIndex;
	char _receiveIndex = 0;
	long int _sendByte;
	char _receiveByte;
	char _receiveInvertedByte;
	char _hasNewInput;

//functions
public:
	IRCommunication();
	virtual void Begin();
	virtual void Send(unsigned char data);
	virtual unsigned char Receive();
	void ReceiveData();
	void SendData();
	~IRCommunication();
protected:
private:

}; //IRCommunication

extern IRCommunication * IRCommunicationObj;

#endif //__IRCOMMUNICATION_H__
