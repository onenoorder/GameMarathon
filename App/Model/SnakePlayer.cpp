/* 
* SnakePlayer.cpp
*
* Created: 17-11-2017 16:46:11
* Author: Gerhard
*/


#include "SnakePlayer.h"

// default constructor
SnakePlayer::SnakePlayer(char x, char y, uint16_t color)
{
	this->X = x;
	this->Y = y;
	this->Color = color;
	_snake = new Queue();
	_size = 0;
	_maxSize = 100;
} //SnakePlayer

void SnakePlayer::Move(){
	if(Direction == Up){
		Y--;
		if(Y < 0)
			Y = 240;
	} else if(Direction == Right){
		X++;
		if(X > 320)
			X = 0;
	} else if(Direction == Down){
		Y++;
		if(Y > 240)
			Y = 0;
	} else if(Direction == Left){
		X--;
		if(X < 0)
			X = 320;
	}
}

void SnakePlayer::Draw(MI0283QT9 *LCD){
	_snake->Enqueue(X, Y);
	LCD->fillCircle(X, Y, 1, Color);
	if(_size < _maxSize){
		_size++;
	} else {
		QueueData back = _snake->Dequeue();
		LCD->fillCircle(back.X, back.Y, 1, RGB(0,0,0));
	}
}

// default destructor
SnakePlayer::~SnakePlayer()
{
} //~SnakePlayer
