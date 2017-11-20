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

	_players[0] = new SnakePlayer(50,50, RGB(255,0,0));
	_currentPlayer = _players[0];
	_playerCount++;
}

void Snake::Update(){
	Game::Update();
	_InputController->UpdateInput();
	Serial.println(_InputController->NunchuckAnalogX);

	if(_InputController->NunchuckAnalogX > 200){
		Serial.println("right");
		_currentPlayer->Direction = Right;
		}else if(_InputController->NunchuckAnalogY > 200){
		Serial.println("Up");
		_currentPlayer->Direction = Up;
	}
	else if(_InputController->NunchuckAnalogX < 50){
		Serial.println("Left");
		_currentPlayer->Direction = Left;
	}
	else if(_InputController->NunchuckAnalogY < 50){
		Serial.println("Down");
		_currentPlayer->Direction = Down;
	}
	_currentPlayer->Move();
	_currentPlayer->Draw(_LCD);
	_delay_ms(100);
}

// default destructor
Snake::~Snake()
{
} //~Snake
