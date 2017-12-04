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
	uint16_t RockGlowColor;
	uint16_t WallColor;
	uint16_t BackgroundColor;
	enum GridCell{
		 Walkable = 0,
		 Explotion = 16,
		 Explotion_1 = 20,
		 Explotion_2 = 24,
		 Explotion_3 = 28,
		 Bomb = 32,
		 Rock = 64,
		 Wall = 128
	};
protected:
private:
	BombermanPlayer *_players[4];
	Queue<BombermanBomb*> * _bombs;
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
		BOMBERMAN_WIN = 20,
		BOMBERMAN_LOSE = 24,
		BOMBERMAN_ACTIONS = 28,
		BOMBERMAN_PLACE_BOM = 32
	};	

//functions
public:
	Bomberman(unsigned char ID, unsigned char playerCount, MI0283QT9 *LCD, InputController *inputController, Communication *communication);
	virtual void Load();
	virtual void Update();
	void DrawGridCell(char x, char y);
	~Bomberman();
protected:
private:
	unsigned char GetOutputData();
	void DoInputData(unsigned char data);
	void UpdatePlayerInput();
	void UpdateBombs();
	void UpdatePlayers();

}; //Bomberman

#endif //__BOMBERMAN_H__
