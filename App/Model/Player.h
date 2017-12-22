/* 
* Player.h
*
* Created: 7-12-2017 10:46:54
* Author: Mikena
*/

#ifndef __PLAYER_H__
#define __PLAYER_H__

enum WinningState{
	PL_WIN, PL_LOSE
};

class Player
{
public:
	unsigned int Score;
	char Alive;
	unsigned char WinState;

//functions
public:
	Player ();
	virtual ~Player();

}; //Player

#endif //__PLAYER_H__
