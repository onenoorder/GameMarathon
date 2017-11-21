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
		BOMBERMAN_PLAYER0 = 0,
		BOMBERMAN_PLAYER1 = 1,
		BOMBERMAN_PLAYER2 = 2,
		BOMBERMAN_PLAYER3 = 3,
		BOMBERMAN_PLAYERS = 3,
		BOMBERMAN_MOVE_UP = 4,
		BOMBERMAN_MOVE_DOWN = 8,
		BOMBERMAN_MOVE_LEFT = 12,
		BOMBERMAN_MOVE_RIGHT = 16,
		BOMBERMAN_VIEW_UP = 20,
		BOMBERMAN_VIEW_DOWN = 24,
		BOMBERMAN_VIEW_LEFT = 28,
		BOMBERMAN_VIEW_RIGHT = 32,
		BOMBERMAN_PLACE_BOM = 36,
		BOMBERMAN_WIN = 40,
		BOMBERMAN_LOSE = 44,
		BOMBERMAN_ACTIONS = 56
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
	unsigned char GetOutputData();
	void DoInputData(unsigned char data);

}; //Bomberman

#endif //__BOMBERMAN_H__
