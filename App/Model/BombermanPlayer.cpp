/* 
* BombermanPlayer.cpp
*
* Created: 17-11-2017 12:42:19
* Author: Mikena
*/


#include "BombermanPlayer.h"

// default constructor
BombermanPlayer::BombermanPlayer(char X,char Y, uint16_t color)
{
	this->X = X;
	this->Y = Y;
	direction = Up;
	this->color = color;
} //BombermanPlayer

// default destructor
BombermanPlayer::~BombermanPlayer()
{
} //~BombermanPlayer
