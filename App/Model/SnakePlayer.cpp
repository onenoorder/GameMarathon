/* 
* SnakePlayer.cpp
*
* Created: 17-11-2017 16:46:11
* Author: Gerhard
*/

#include "SnakePlayer.h"

// default constructor
SnakePlayer::SnakePlayer(char x, char y, uint16_t color, Snake *game) : Player()
{
	this->X = x;
	this->Y = y;
	this->Color = color;
	SnakeSize = 10;
	this->_game = game;
} //SnakePlayer

//move snake functie, afhankelijk van 'Direction' wordt deze verplaatst
void SnakePlayer::Move(){
	if(Direction == Up){
		Y--;
		if(Y < 0)
			Y = 23;
	} else if(Direction == Right){
		X++;
		if(X >= 32)
			X = 0;
	} else if(Direction == Down){
		Y++;
		if(Y >= 24)
			Y = 0;
	} else if(Direction == Left){
		X--;
		if(X < 0)
			X = 31;
	}
	CheckNewLocation();
	_game->Grid[X][Y] = 1;
}

//nieuwe locatie waar de snake naartoe gaat controleren, is element een 1 dan is op de nieuwe locatie een andere snake, en dus dood. .
void SnakePlayer::CheckNewLocation(){
	if(_game->Grid[X][Y] > 0){
		this->Alive = 0;
	}
}

//teken slang
void SnakePlayer::Draw(MI0283QT9 *LCD){
	LCD->fillRect(X*SnakeSize, Y*SnakeSize, SnakeSize, SnakeSize, Color);
}

// default destructor
SnakePlayer::~SnakePlayer()
{
} //~SnakePlayer
