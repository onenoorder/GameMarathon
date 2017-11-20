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
	char Blastpower;
	char Bombs;
	DirectionEnum Direction;
	uint16_t Color;
protected:
private:

//functions
public:
	void DrawPlayer();
	BombermanPlayer(char X,char Y,uint16_t color);
	//void Input(InputController *inputController)
	//void Move();
	//void Draw(MI0283QT9 *LCD);
	~BombermanPlayer();
protected:
private:


}; //BombermanPlayer

#endif //__BOMBERMANPLAYER_H__
