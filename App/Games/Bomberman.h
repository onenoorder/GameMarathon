/* 
* Bomberman.h
*
* Created: 14-11-2017 14:05:47
* Author: Gerhard
*/

#ifndef __BOMBERMAN_H__
#define __BOMBERMAN_H__

#include "Game.h"
#include "../Model/BombermanPlayer.h"
#include "../Model/BombermanBomb.h"
#include "../Lib/Queue/Queue.h"
class BombermanPlayer;
class BombermanBomb;

class Bomberman : public Game
{
//variables
public:
	unsigned char **Grid;
	char GridBlockSize;
	char MaxX;
	char MaxY;
		char OffsetX;
		char OffsetY;
	uint16_t RockColor;
	uint16_t WallColor;
	uint16_t BackgroundColor;
	enum GridCell{
		 Walkable = 0,
		 Wall = 32,
		 Rock = 64,
		 Bomb = 128		
	};
protected:
private:

	BombermanPlayer *_players[4];
	unsigned char BombStartIndex;
	unsigned char BombsActiveCount;

	Queue<BombermanBomb*> * _bombs;
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
