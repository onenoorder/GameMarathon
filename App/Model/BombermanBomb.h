/* 
* BombermanBomb.h
*
* Created: 20-11-2017 15:54:40
* Author: Mikena
*/

#include "BombermanPlayer.h"
#ifndef __BOMBERMANBOMB_H__
#define __BOMBERMANBOMB_H__


class BombermanBomb
{
//variables
public:
	char X;
	char Y;
	BombermanPlayer * Player;
	int TimePlaced;
	char BombIndex;
protected:
private:

//functions
public:
	BombermanBomb(char X, char Y,int TimePlaced, BombermanPlayer * Player , int index);
	~BombermanBomb();
protected:
private:


}; //BombermanBomb

#endif //__BOMBERMANBOMB_H__