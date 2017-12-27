/* 
* RockPaperScissorsPlayer.h
*
* Created: 27-12-2017 19:20:57
* Author: Gerhard
*/

#ifndef __ROCKPAPERSCISSORSPLAYER_H__
#define __ROCKPAPERSCISSORSPLAYER_H__

#include "Player.h"
#include "../Games/RockPaperScissors.h"

class RockPaperScissors;
class RockPaperScissorsPlayer : public Player
{
//variables
public:
	char ID;
	uint16_t Color;
	DirectionEnum Direction;
protected:
private:
	RockPaperScissors *_game;

//functions
public:
	RockPaperScissorsPlayer(char ID, uint16_t color, RockPaperScissors *game);
	void Draw(MI0283QT9 *LCD);
	~RockPaperScissorsPlayer();
protected:
private:

}; //RockPaperScissorsPlayer

#endif //__ROCKPAPERSCISSORSPLAYER_H__
