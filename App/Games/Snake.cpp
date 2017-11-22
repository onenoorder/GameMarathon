/* 
* Snake.cpp
*
* Created: 17-11-2017 16:38:25
* Author: Gerhard
*/

#include "Snake.h"

// default constructor
Snake::Snake(unsigned char ID, MI0283QT9 *LCD, InputController *inputController) : Game(ID, LCD, inputController)
{
	_backgroundColor = RGB(0, 0, 0);
	_playerCount = 0;
} //Snake

void Snake::Load()
{
	// Background
	_LCD->fillScreen(_backgroundColor);

	_players[0] = new SnakePlayer(5,5, RGB(255,0,0));
	_players[0]->Direction = Right;
	_playerCount++;
	_players[1] = new SnakePlayer(315,235, RGB(0,0,255));
	_players[1]->Direction = Left;
	_playerCount++;
	_currentPlayer = _players[0];
}

void Snake::Update(){
	Game::Update();
	_InputController->UpdateInput();

	if(_InputController->NunchuckAnalogX > 200){
		if(_currentPlayer->Direction != Left)
			_currentPlayer->Direction = Right;
	} else if(_InputController->NunchuckAnalogY > 200){
		if(_currentPlayer->Direction != Down)
			_currentPlayer->Direction = Up;
	} else if(_InputController->NunchuckAnalogX < 50){
		if(_currentPlayer->Direction != Right)
			_currentPlayer->Direction = Left;
	} else if(_InputController->NunchuckAnalogY < 50){
		if(_currentPlayer->Direction != Up)
			_currentPlayer->Direction = Down;
	}
	_currentPlayer->Move();
	_currentPlayer->Draw(_LCD);
	_players[1]->Move();
	_players[1]->Draw(_LCD);
	_delay_ms(100);
}

// default destructor
Snake::~Snake()
{
} //~Snake
