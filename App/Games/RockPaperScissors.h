/* 
* RockPaperScissors.h
*
* Created: 27-12-2017 17:58:12
* Author: Gerhard
*/

#ifndef __ROCKPAPERSCISSORS_H__
#define __ROCKPAPERSCISSORS_H__

#include "Game.h"
#include "../Views/GameEndView.h"
#include "../Model/RockPaperScissorsPlayer.h"

class RockPaperScissorsPlayer;
class RockPaperScissors : public Game
{
//variables
public:
	uint16_t BackgroundColor;
protected:
private:
	RockPaperScissorsPlayer *_players[2];
	RockPaperScissorsPlayer *_currentPlayer;
	unsigned char _turn;
	int _turnTime;
	
	enum RockPaperScissorsData{
		ROCKPAPERSCISSORS_PLAYER0 = 0,
		ROCKPAPERSCISSORS_PLAYER1 = 1,
		ROCKPAPERSCISSORS_PLAYERS = 1,
		ROCKPAPERSCISSORS_ROCK = 2,
		ROCKPAPERSCISSORS_PAPER = 4,
		ROCKPAPERSCISSORS_SCISSORS = 6,
		ROCKPAPERSCISSORS_WIN = 8,
		ROCKPAPERSCISSORS_LOSE = 10,
		ROCKPAPERSCISSORS_ACTIONS = 14
	};

//functions
public:
	RockPaperScissors(MI0283QT9 *LCD, InputController *inputController, Communication *communication);
	virtual void Load();
	virtual void Update();
	~RockPaperScissors();
protected:
	virtual void EndGame();
private:
	virtual unsigned char GetOutputData();
	virtual void DoInputData(unsigned char data);
	void UpdatePlayerInput();

}; //RockPaperScissors

#endif //__ROCKPAPERSCISSORS_H__
