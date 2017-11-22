/* 
* Snake.h
*
* Created: 17-11-2017 16:38:25
* Author: Gerhard
*/

#include "Game.h"
#include "../Model/SnakePlayer.h"

#ifndef __SNAKE_H__
#define __SNAKE_H__


class Snake : public Game
{
//variables
public:
protected:
private:
	uint16_t _backgroundColor;
	SnakePlayer *_players[4];
	SnakePlayer *_currentPlayer;
	SnakePlayer *_secondPlayer;
	char _playerCount;

//functions
public:
	Snake(unsigned char ID, MI0283QT9 *LCD, InputController *inputController);
	virtual void Load();
	virtual void Update();
	~Snake();
protected:
private:

}; //Snake

#endif //__SNAKE_H__
