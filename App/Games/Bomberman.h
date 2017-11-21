/* 
* Bomberman.h
*
* Created: 14-11-2017 14:05:47
* Author: Gerhard
*/
#include "Game.h"
#include "../Model/BombermanPlayer.h"
#include "../Model/BombermanBomb.h"
#ifndef __BOMBERMAN_H__
#define __BOMBERMAN_H__


class Bomberman : public Game
{
//variables
public:
protected:
private:
	char **_grid;
	char _gridBlockSize;
	char _maxX;
	char _maxY;
	char _offsetX;
	char _offsetY;
	char Walkable = 0;
	char Wall = 32;
	char Rock = 64;
	char Bomb = 128;
	uint16_t _rockColor;
	uint16_t _wallColor;
	uint16_t _backgroundColor;
	BombermanPlayer *_players[4];
	unsigned char BombStartIndex;
	unsigned char BombsActiveCount;
	BombermanBomb * _bombs[16];
	BombermanPlayer *_currentPlayer;
	enum BombermanData{
		PLAYER0 = 0,
		PLAYER1 = 1,
		PLAYER2 = 2,
		PLAYER3 = 3,
		MOVE_UP = 4,
		MOVE_DOWN = 8,
		MOVE_LEFT = 12,
		MOVE_RIGHT = 16,
		VIEW_UP = 20,
		VIEW_DOWN = 24,
		VIEW_LEFT = 28,
		VIEW_RIGHT = 32,
		PLACE_BOM = 36,
		WIN = 40,
		LOSE = 44
	};
	

//functions
public:
	Bomberman(unsigned char ID, MI0283QT9 *LCD, InputController *inputController);
	virtual void Load();
	virtual void Update();

	~Bomberman();
protected:
private:
	void drawGridCell(char x, char y);

}; //Bomberman

#endif //__BOMBERMAN_H__
