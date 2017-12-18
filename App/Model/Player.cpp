/* 
* Player.cpp
*
* Created: 7-12-2017 10:46:54
* Author: Mikena
*/


#include "Player.h"

// default constructor
Player::Player(){
	Score = 0;
	this->Alive = 1;
	WinState = PL_WIN;
}

// virtual destructor
Player::~Player()
{
} //~Player
