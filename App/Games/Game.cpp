/* 
* Game.cpp
*
* Created: 14-11-2017 13:53:46
* Author: Gerhard
*/


#include "Game.h"

Game::Game( unsigned char ID, unsigned char playerCount, MI0283QT9 *LCD, InputController *inputController, Communication *communication) :View(LCD,inputController)  {

	NewFrame = 0;
	PlayerID = ID;
	PlayerCount = playerCount;
	_communication = communication;
}

void Game::Update(){

	NewFrame = 0;
}

// virtual destructor
Game::~Game()
{
} //~Game
