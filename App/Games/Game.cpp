/* 
* Game.cpp
*
* Created: 14-11-2017 13:53:46
* Author: Gerhard
*/


#include "Game.h"

Game::Game(MI0283QT9 *LCD){
	_LCD = LCD;
	_InputController = new InputController();
	_InputController->UpdateInput();
	NewFrame = 0;
}

void Game::Update(){
	NewFrame = 0;
}

// virtual destructor
Game::~Game()
{
} //~Game
