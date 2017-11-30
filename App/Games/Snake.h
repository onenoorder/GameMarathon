/* 
* Snake.h
*
* Created: 17-11-2017 16:38:25
* Author: Gerhard
*/



#ifndef __SNAKE_H__
#define __SNAKE_H__
#include "Game.h"
#include "../Model/SnakePlayer.h"

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

	enum SnakeData{
		SNAKE_PLAYER0 = 0,
		SNAKE_PLAYER1 = 1,
		SNAKE_PLAYER2 = 2,
		SNAKE_PLAYER3 = 3,
		SNAKE_PLAYERS = 3,
		SNAKE_MOVE_UP = 4,
		SNAKE_MOVE_DOWN = 8,
		SNAKE_MOVE_LEFT = 12,
		SNAKE_MOVE_RIGHT = 16,
		SNAKE_WIN = 20,
		SNAKE_LOSE = 24,
		SNAKE_ACTIONS = 28
	};

//functions
public:
	Snake(unsigned char ID, unsigned char playerCount, MI0283QT9 *LCD, InputController *inputController, Communication *communication);
	virtual void Load();
	virtual void Update();
	~Snake();
protected:
private:
	unsigned char GetOutputData();
	void DoInputData(unsigned char data);

}; //Snake

#endif //__SNAKE_H__
