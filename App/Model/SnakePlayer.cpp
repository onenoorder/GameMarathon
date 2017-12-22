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
		if(Y < 0){
			Y = 23;
			Score += 50;
		}
	} else if(Direction == Right){
		X++;
		if(X >= 32){
			X = 0;
			Score += 50;
		}
	} else if(Direction == Down){
		Y++;
		if(Y >= 24){
			Y = 0;
			Score += 50;
		}
	} else if(Direction == Left){
		X--;
		if(X < 0) {
			X = 31;
			Score += 50;
		}
	}
	CheckNewLocation();
	_game->Grid[X][Y] = 1;
}

//nieuwe locatie waar de snake naartoe gaat controleren, zit er een waarde op de locatie dan is daar al iets, en dus gaat de speler dood
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
