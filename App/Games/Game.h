/* 
* Game.h
*
* Created: 14-11-2017 13:53:46
* Author: Gerhard
*/

#ifndef __GAME_H__
#define __GAME_H__

#include "../Lib/MI0283QT9/MI0283QT9.h"
#include "../Helpers/InputController.h"
#include "../Communication/SerialCommunication.h"
#include "../Views/View.h"

enum DirectionEnum {
	Left = 1,
	Up = 2,
	Right = 3,
	Down = 4
};

class Game : public View
{
public:
	unsigned char PlayerID;
	unsigned char PlayerCount;
protected:
	char TransitionCounter;
	int EndTime;

//functions
public:
	virtual void Load() = 0;
	virtual void Update();
	virtual ~Game();
protected:
	Game(MI0283QT9 *LCD, InputController *inputController,Communication *communication);
	virtual void EndGame() = 0;

}; //Game

#endif //__GAME_H__
