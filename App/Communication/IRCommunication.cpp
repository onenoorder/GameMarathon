/* 
* IRCommunication.cpp
*
* Created: 13-12-2017 14:04:34
* Author: Mikena
*/
char sendByte;

#include "IRCommunication.h"

// default constructor
IRCommunication::IRCommunication()
{
} //IRCommunication


void IRCommunication::Begin(){

}

void IRCommunication::Send(unsigned char data){

}

unsigned char IRCommunication::Receive(){
	while(sendByte != 0);
	return sendByte;
}
// default destructor
IRCommunication::~IRCommunication()
{
} //~IRCommunication
