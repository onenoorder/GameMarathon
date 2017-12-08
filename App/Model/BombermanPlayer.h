/* 
* BombermanPlayer.h
*
* Created: 17-11-2017 12:42:19
* Author: Mikena & Gerhard
*/

#ifndef __BOMBERMANPLAYER_H__
#define __BOMBERMANPLAYER_H__

#include "../Games/Bomberman.h"
#include "Player.h"
class Bomberman;
class BombermanPlayer : public Player
{
//variables
public:
	int BombTime;
	char X;
	char Y;
	char Blastpower;
	char Bombs;
	char MaxBombs;
	char PlayerUpdated;
	DirectionEnum Direction;
	uint16_t Color;
	uint16_t ShadowColor;
	unsigned char PlaceBomb;
protected:
private:
	Bomberman * _game;

//functions
public:
	void DrawPlayer(MI0283QT9 * LCD);
	void Move();
	BombermanPlayer(char X,char Y,uint16_t color, Bomberman * game);
	//void Input(InputController *inputController)
	//void Move();
	//void Draw(MI0283QT9 *LCD);
	~BombermanPlayer();
protected:
private:


}; //BombermanPlayer

#endif //__BOMBERMANPLAYER_H__
