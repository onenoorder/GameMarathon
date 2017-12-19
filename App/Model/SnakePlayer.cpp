/* 
* SnakePlayer.cpp
*
* Created: 17-11-2017 16:46:11
* Author: Gerhard
*/

#include "SnakePlayer.h"

// default constructor
SnakePlayer::SnakePlayer(short x, short y, uint16_t color, Snake *game) : Player()
{
	this->X = x;
	this->Y = y;
	this->Color = color;
	MaxSize = 2;
	MinSize = 2;
	Size = 0;
	SnakeSize = 10;
	SnakeQueue = new Queue<SnakeQueueData>(12);
	this->_game = game;
} //SnakePlayer

//move snake functie, afhankelijk van 'Direction' wordt deze verplaatst
void SnakePlayer::Move(){
	if(Direction == Up){
		Y -= SnakeSize;
		if(Y <= 0)
			Y = 240 - SnakeSize/2;
	} else if(Direction == Right){
		X += SnakeSize;
		if(X >= 320)
			X = 0 + SnakeSize/2;
	} else if(Direction == Down){
		Y += SnakeSize;
		if(Y >= 240)
			Y = 0 +  SnakeSize/2;
	} else if(Direction == Left){
		X -= SnakeSize;
		if(X <= 0)
			X = 320 - SnakeSize/2;
	}
	CheckNewLocation();
}

//nieuwe locatie waar de snake naartoe gaat controleren, is element een 1 dan is op de nieuwe locatie een andere snake, en dus dood. .
void SnakePlayer::CheckNewLocation(){
	unsigned char element = _game->CheckLocation(X-SnakeSize/2, Y-SnakeSize/2);
	if(element == 1 && X-SnakeSize/2 > 0 && Y-SnakeSize/2 > 0){
		this->Alive = 0;
	}
}

//teken slang
void SnakePlayer::Draw(MI0283QT9 *LCD){
	SnakeQueueData data = {X,Y};
	SnakeQueue->Enqueue(data);
	LCD->fillCircle(X, Y, SnakeSize/2, Color);
	if(Size < MaxSize){
		Size++;
	} else {
		SnakeQueueData back = SnakeQueue->Dequeue();
		LCD->fillCircle(back.X, back.Y, SnakeSize/2, RGB(0,0,0));
	}
}

// default destructor
SnakePlayer::~SnakePlayer()
{
} //~SnakePlayer
