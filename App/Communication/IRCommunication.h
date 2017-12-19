/* 
* IRCommunication.h
*
* Created: 13-12-2017 14:04:35
* Author: Mikena
*/


#ifndef __IRCOMMUNICATION_H__
#define __IRCOMMUNICATION_H__
#include "Communication.h"
class IRCommunication: public Communication
{
//variables
public:
protected:
private:

//functions
public:
	IRCommunication();
	virtual void Begin();
	virtual void Send(unsigned char data);
	virtual unsigned char Receive();
	~IRCommunication();
protected:
private:
	IRCommunication( const IRCommunication &c );
	IRCommunication& operator=( const IRCommunication &c );

}; //IRCommunication

#endif //__IRCOMMUNICATION_H__
