/* 
* Communication.h
*
* Created: 30-11-2017 10:18:48
* Author: Gerhard
*/


#ifndef __COMMUNICATION_H__
#define __COMMUNICATION_H__

class Communication
{
//functions
public:
	virtual ~Communication(){}
	virtual void Begin() = 0;
	virtual void Send(unsigned char data) = 0;
	virtual unsigned char Receive() = 0;

}; //Communication

#endif //__COMMUNICATION_H__
