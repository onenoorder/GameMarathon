/* 
* BombermanBomb.h
*
* Created: 20-11-2017 15:54:40
* Author: Mikena
*/


#ifndef __BOMBERMANBOMB_H__
#define __BOMBERMANBOMB_H__
#include "BombermanPlayer.h"
class BombermanPlayer;
class Bomberman;
class BombermanBomb
{
//variables
public:
	char X;
	char Y;
	BombermanPlayer * Player;
	int TimePlaced;
	char BombIndex;
	char Exploding;
	char Ticks;
protected:
private:
	Bomberman * _game;
//functions
public:
	BombermanBomb(char X, char Y,int TimePlaced, BombermanPlayer * Player , int index, Bomberman * game);
	void Tick(MI0283QT9 * LCD);
	void Explode(MI0283QT9 * LCD);
	~BombermanBomb();
protected:
private:


}; //BombermanBomb

#endif //__BOMBERMANBOMB_H__
