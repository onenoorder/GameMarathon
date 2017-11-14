/* 
* Game.h
*
* Created: 14-11-2017 13:53:46
* Author: Gerhard
*/


#ifndef __GAME_H__
#define __GAME_H__


class Game
{
//functions
public:
	virtual ~Game();
	virtual void Method1()=0;//make Game not instantiable
	virtual void Method2();
	void Method3();

}; //Game

#endif //__GAME_H__
