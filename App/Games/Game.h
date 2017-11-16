/* 
* Game.h
*
* Created: 14-11-2017 13:53:46
* Author: Gerhard
*/

#include "../Lib/MI0283QT9/MI0283QT9.h"

#ifndef __GAME_H__
#define __GAME_H__


class Game
{
protected:
	MI0283QT9 *_LCD;
//functions
public:
	virtual void Load() = 0;
	virtual ~Game();
protected:
	void InitScreen();

}; //Game

#endif //__GAME_H__
