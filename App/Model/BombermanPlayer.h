/* 
* BombermanPlayer.h
*
* Created: 17-11-2017 12:42:19
* Author: Mikena
*/
#include "../Games/Game.h"

#ifndef __BOMBERMANPLAYER_H__
#define __BOMBERMANPLAYER_H__


class BombermanPlayer
{
//variables
public:
	char X;
	char Y;
	char blastpower;
	char Bombs;
	DirectionEnum direction;
	uint16_t color;
protected:
private:

//functions
public:
	BombermanPlayer(char X,char Y,uint16_t color);
	~BombermanPlayer();
protected:
private:


}; //BombermanPlayer

#endif //__BOMBERMANPLAYER_H__