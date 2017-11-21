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
	unsigned char GetOutputData();
	void DoInputData(unsigned char data);
	~BombermanBomb();
protected:
private:


}; //BombermanBomb

#endif //__BOMBERMANBOMB_H__
