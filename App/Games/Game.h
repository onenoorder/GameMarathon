/* 
* Game.h
*
* Created: 14-11-2017 13:53:46
* Author: Gerhard
*/

#include "../Lib/MI0283QT9/MI0283QT9.h"
#include "../Helpers/InputController.h"

#ifndef __GAME_H__
#define __GAME_H__

enum DirectionEnum {
	Left = 1,
	Up = 2,
	Right = 3,
	Down = 4
};

class Game
{
public:
	unsigned int Timer = 0;
	unsigned int GameTime = 0;
protected:
	MI0283QT9 *_LCD;
	InputController * _InputController;
//functions
public:
	virtual void Load() = 0;
	virtual void Update() = 0;

	virtual ~Game();
protected:
	Game(MI0283QT9 *LCD);
}; //Game

#endif //__GAME_H__
