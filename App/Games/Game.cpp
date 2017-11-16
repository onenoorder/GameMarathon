/* 
* Game.cpp
*
* Created: 14-11-2017 13:53:46
* Author: Gerhard
*/


#include "Game.h"

void Game::InitScreen(){
	_LCD = new MI0283QT9();
	_LCD->begin();
}

// virtual destructor
Game::~Game()
{
} //~Game
