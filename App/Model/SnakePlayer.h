/* 
* SnakePlayer.h
*
* Created: 17-11-2017 16:46:11
* Author: Gerhard
*/

#include "../Games/Game.h"
#include "../Lib/Queue/Queue.h"

#ifndef __SNAKEPLAYER_H__
#define __SNAKEPLAYER_H__

class SnakePlayer
{
//variables
public:
	short X;
	short Y;
	uint16_t Color;
	DirectionEnum Direction;
protected:
private:
	Queue<SnakeQueueData> *_snake;
	unsigned char _size;
	unsigned char _maxSize;

//functions
public:
	SnakePlayer(char x, char y, uint16_t color);
	void Move();
	void Draw(MI0283QT9 *LCD);
	~SnakePlayer();
protected:
private:

}; //SnakePlayer

#endif //__SNAKEPLAYER_H__
