/* 
* SnakePlayer.h
*
* Created: 17-11-2017 16:46:11
* Author: Gerhard
*/

#ifndef __SNAKEPLAYER_H__
#define __SNAKEPLAYER_H__

#include "../Games/Snake.h"
#include "../Lib/Queue/Queue.h"
#include "Player.h"

class Snake;
class SnakePlayer : public Player
{
//variables
public:
	short X;
	short Y;
	unsigned char Size;
	unsigned char MaxSize;
	unsigned char MinSize;
	unsigned char SnakeSize;
	uint16_t Color;
	DirectionEnum Direction;
	unsigned char PlaceCookie;
	Queue<SnakeQueueData> *SnakeQueue;
protected:
private:
	Snake *_game;

//functions
public:
	SnakePlayer(short x, short y, uint16_t color, Snake *game);
	void Move();
	void Draw(MI0283QT9 *LCD);
	~SnakePlayer();
protected:
private:
	void CheckNewLocation();

}; //SnakePlayer

#endif //__SNAKEPLAYER_H__
