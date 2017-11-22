/* 
* Master.h
*
* Created: 14-11-2017 13:54:38
* Author: Gerhard
*/
#ifndef __MASTER_H__
#define __MASTER_H__

#include "Data.h"

class Master
{
//variables
public:
protected:
private:

//functions
public:
	Master();
	void SendTo(int ID);
	void ReceiveFrom(int ID);
	~Master();
protected:
private:

}; //Master

#endif //__MASTER_H__
