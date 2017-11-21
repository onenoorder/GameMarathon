/* 
* BombermanBomb.cpp
*
* Created: 20-11-2017 15:54:39
* Author: Mikena
*/


#include "BombermanBomb.h"



 BombermanBomb::BombermanBomb(char X, char Y,int TimePlaced, BombermanPlayer * Player , int index)
{
	this->X = X;
	this->Y = Y;
	this->TimePlaced = TimePlaced;
	this->BombIndex = index;
	this->Player = Player;
	this->Exploding = 0;
}

// default destructor
BombermanBomb::~BombermanBomb()
{
} //~BombermanBomb
