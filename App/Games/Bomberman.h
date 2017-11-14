/* 
* Bomberman.h
*
* Created: 14-11-2017 14:05:47
* Author: Gerhard
*/

#include "Game.h"

#ifndef __BOMBERMAN_H__
#define __BOMBERMAN_H__


class Bomberman : public Game
{
//variables
public:
protected:
private:

//functions
public:
	Bomberman();
	~Bomberman();
protected:
private:
	Bomberman( const Bomberman &c );
	Bomberman& operator=( const Bomberman &c );

}; //Bomberman

#endif //__BOMBERMAN_H__
