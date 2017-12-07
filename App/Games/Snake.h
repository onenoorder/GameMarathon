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

class SnakePlayer;
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
	unsigned int _cookieTime;
	unsigned char _cookieDelay;
	uint16_t _cookieColor;
	unsigned char _cookieSize;
	unsigned char _maxCookies;
	Queue<SnakeCookie> *_cookies;

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
		SNAKE_ACTIONS = 28,
		SNAKE_COOKIE = 32,
		SNAKE_SET_COOKIE = 64
	};

//functions
public:
	Snake(unsigned char ID, unsigned char playerCount, MI0283QT9 *LCD, InputController *inputController, Communication *communication);
	virtual void Load();
	virtual void Update();
	unsigned char CheckLocation(short x, short y);
	~Snake();
protected:
private:
	unsigned char GetOutputData();
	void DoInputData(unsigned char data);
	void UpdatePlayerInput();
	void UpdatePlayers();
	void CookieTime();
	void PlaceCookie(short x, short y);
	void UpdateCookies();

}; //Snake

#endif //__SNAKE_H__
