/* 
* Game.cpp
*
* Created: 14-11-2017 13:53:46
* Author: Gerhard
*/


#include "Game.h"

Game::Game(unsigned char ID, MI0283QT9 *LCD, InputController *inputController){
	_LCD = LCD;
	_InputController = inputController;
	_InputController->UpdateInput();
	NewFrame = 0;
	PlayerID = ID;
	
	if(PlayerID == 0)
		_master = new Master();
	else
		_slave = new Slave(PlayerID);
}

void Game::Update(){
	NewFrame = 0;
}

// virtual destructor
Game::~Game()
{
} //~Game
