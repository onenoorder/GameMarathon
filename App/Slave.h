/* 
* Slave.h
*
* Created: 14-11-2017 13:54:24
* Author: Gerhard
*/


#ifndef __SLAVE_H__
#define __SLAVE_H__


class Slave
{
//variables
public:
	char ID;
protected:
private:

//functions
public:
	Slave(char ID);
	~Slave();
protected:
private:
	Slave( const Slave &c );
	Slave& operator=( const Slave &c );

}; //Slave

#endif //__SLAVE_H__
