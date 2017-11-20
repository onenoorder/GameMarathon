/* 
* Bomberman.h
*
* Created: 14-11-2017 14:05:47
* Author: Gerhard
*/
#include "Game.h"
#include "../Model/BombermanPlayer.h"

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
	char Player1 = 1;
	char Player2 = 2;
	uint16_t _rockColor;
	uint16_t _wallColor;
	uint16_t _backgroundColor;
	BombermanPlayer *_players;
	BombermanPlayer *_currentPlayer;
	

//functions
public:
	Bomberman(MI0283QT9 *LCD);
	virtual void Load();
	virtual void Update();

	~Bomberman();
protected:
private:
	void drawGridCell(char x, char y);

}; //Bomberman

#endif //__BOMBERMAN_H__
