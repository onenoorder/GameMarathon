/* 
* Snake.cpp
*
* Created: 17-11-2017 16:38:25
* Author: Gerhard
*/

#include "Snake.h"

// default constructor
Snake::Snake(unsigned char ID, unsigned char playerCount, MI0283QT9 *LCD, InputController *inputController, Communication *communication) : Game(ID, playerCount, LCD, inputController, communication)
{
	_backgroundColor = RGB(0, 0, 0);
	_playerCount = playerCount;
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
	_currentPlayer = _players[PlayerID];
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

	if(PlayerID == 0){
		OutputData = GetOutputData();
		Serial.write(OutputData);

		if(PlayerCount > 1){
			while(!Serial.available());
			InputData = Serial.read();
			DoInputData(InputData);
		}
	} else {
		if(PlayerCount > 1){
			while(!Serial.available());
			InputData = Serial.read();
			DoInputData(InputData);
		}

		OutputData = GetOutputData();
		Serial.write(OutputData);
	}
}

unsigned char Snake::GetOutputData(){
	unsigned char data = 0;
	data = PlayerID;
	switch(_currentPlayer->Direction){
		case Up:
			data |= SNAKE_MOVE_UP;
			break;
		case Left:
			data |= SNAKE_MOVE_LEFT;
			break;
		case Right:
			data |= SNAKE_MOVE_RIGHT;
			break;
		case Down:
			data |= SNAKE_MOVE_DOWN;
			break;
	};
	DoInputData(data);
	return data;
}

void Snake::DoInputData(unsigned char data){
	if(data != 0){
		SnakePlayer *player = _players[data & SNAKE_PLAYERS];

		if((data & SNAKE_ACTIONS) > 0){
			switch(data & SNAKE_ACTIONS){
				case SNAKE_MOVE_UP:
				player->Direction = Up;
				break;
				case SNAKE_MOVE_LEFT:
				player->Direction = Left;
				break;
				case SNAKE_MOVE_RIGHT:
				player->Direction = Right;
				break;
				case SNAKE_MOVE_DOWN:
				player->Direction = Down;
				break;
			};
			player->Move();
			player->Draw(_LCD);
		}
	}
}

// default destructor
Snake::~Snake()
{
} //~Snake
