/* 
* SnakePlayer.cpp
*
* Created: 17-11-2017 16:46:11
* Author: Gerhard
*/

#include "SnakePlayer.h"

// default constructor
SnakePlayer::SnakePlayer(short x, short y, uint16_t color)
{
	this->X = x;
	this->Y = y;
	this->Color = color;
	_maxSize = 2;
	_size = 0;
	_snakeSize = 10;
	_snake = new Queue<SnakeQueueData>(30);
} //SnakePlayer

void SnakePlayer::Move(){
	if(Direction == Up){
		Y -= _snakeSize;
		if(Y <= 0)
			Y = 240 - _snakeSize/2;
	} else if(Direction == Right){
		X += _snakeSize;
		if(X >= 320)
			X = 0 + _snakeSize/2;
	} else if(Direction == Down){
		Y += _snakeSize;
		if(Y >= 240)
			Y = 0 +  _snakeSize/2;
	} else if(Direction == Left){
		X -= _snakeSize;
		if(X <= 0)
			X = 320 - _snakeSize/2;
	}
}

void SnakePlayer::Draw(MI0283QT9 *LCD){
	SnakeQueueData data = {X,Y};
	_snake->Enqueue(data);
	LCD->fillCircle(X, Y, _snakeSize/2, Color);
	if(_size < _maxSize){
		_size++;
	} else {
		SnakeQueueData back = _snake->Dequeue();
		LCD->fillCircle(back.X, back.Y, _snakeSize/2, RGB(0,0,0));
	}
}

// default destructor
SnakePlayer::~SnakePlayer()
{
} //~SnakePlayer
