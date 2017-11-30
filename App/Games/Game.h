/* 
* Game.h
*
* Created: 14-11-2017 13:53:46
* Author: Gerhard
*/

#ifndef __GAME_H__
#define __GAME_H__

#include "../Lib/MI0283QT9/MI0283QT9.h"
#include "../Helpers/InputController.h"
#include "../Communication/SerialCommunication.h"

enum DirectionEnum {
	Left = 1,
	Up = 2,
	Right = 3,
	Down = 4
};

class Game
{
public:
	unsigned char Timer = 0;
	unsigned int GameTime = 0;
	unsigned char NewFrame;
	unsigned char PlayerID;
	unsigned char PlayerCount;
protected:
	Communication *_communication;
	MI0283QT9 *_LCD;
	InputController * _InputController;
//functions
public:
	virtual void Load() = 0;
	virtual void Update();

	virtual ~Game();
protected:
	Game(unsigned char ID, unsigned char playerCount, MI0283QT9 *LCD, InputController *inputController,Communication *communication);
}; //Game

#endif //__GAME_H__
