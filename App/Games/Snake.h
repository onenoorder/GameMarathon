/* 
* Snake.h
*
* Created: 17-11-2017 16:38:25
* Author: Gerhard
*/

#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "Game.h"
#include "../Lib/Queue/Queue.h"
#include "../Model/SnakePlayer.h"
#include "../Views/GameEndView.h"

class SnakePlayer;
class Snake : public Game
{
//variables
public:
	char **Grid;
	char MaxX;
	char MaxY;
protected:
private:
	uint16_t _backgroundColor;
	SnakePlayer *_players[2];
	SnakePlayer *_currentPlayer;

	enum SnakeData{
		SNAKE_PLAYER0 = 0,
		SNAKE_PLAYER1 = 1,
		SNAKE_PLAYERS = 1,
		SNAKE_MOVE_UP = 2,
		SNAKE_MOVE_DOWN = 4,
		SNAKE_MOVE_LEFT = 6,
		SNAKE_MOVE_RIGHT = 8,
		SNAKE_WIN = 10,
		SNAKE_LOSE = 12,
		SNAKE_ACTIONS = 14
	};

//functions
public:
	Snake(MI0283QT9 *LCD, InputController *inputController, Communication *communication);
	virtual void Load();
	virtual void Update();
	~Snake();
protected:
	virtual void EndGame();
private:
	unsigned char GetOutputData();
	void DoInputData(unsigned char data);
	void UpdatePlayerInput();
	void UpdatePlayers();

}; //Snake

#endif //__SNAKE_H__
