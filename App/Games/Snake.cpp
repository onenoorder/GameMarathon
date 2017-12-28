/* 
* Snake.cpp
*
* Created: 17-11-2017 16:38:25
* Author: Gerhard
*/

#include "Snake.h"

// default constructor
Snake::Snake(MI0283QT9 *LCD, InputController *inputController, Communication *communication) : Game(LCD, inputController, communication)
{
	_backgroundColor = RGB(0, 0, 0);
	MaxX = 32;
	MaxY = 24;

	// Make grid
	Grid = new char*[MaxX];
	for(char x = 0; x < MaxX; x++)
		Grid[x] = new char[MaxY];
} //Snake

//snakespel laden
void Snake::Load()
{
	// Background
	LCD->fillScreen(_backgroundColor);

	for(unsigned char x = 0; x < MaxX; x++)
		for(unsigned char y = 0; y < MaxY; y++)
			Grid[x][y] = 0;

	_players[0] = new SnakePlayer(MaxX, 0, RGB(255,0,0), this);
	_players[0]->Direction = Right;
	_players[1] = new SnakePlayer(0, MaxY-1, RGB(0,0,255), this);
	_players[1]->Direction = Left;

	_currentPlayer = _players[PlayerID];

	Loaded = 1;
}

//snakespel updaten
void Snake::Update(){
	if(PlayerID == 0 && NewFrame == 0) return;
	Game::Update();
	
	if(EndTime != 0 && EndTime+10 < GameFastTime){
		EndGame();
		return;
	} else if(EndTime != 0){
		return;
	}

	this->UpdatePlayerInput();
	this->UpdatePlayers();
}

//afgelopen spel spel eindigen
void Snake::EndGame(){
	if(TransitionCounter != 8 && GameFastTime % 2 == 0){
		LCD->fillRect(20*TransitionCounter,0 ,20,240,RGB(0,0,0));
		LCD->fillRect(300 - (20 *TransitionCounter),0 ,20,240,RGB(0,0,0));

		TransitionCounter++;
	} else if(TransitionCounter >= 8){
		if(_currentPlayer->WinState == PL_WIN){
			_currentPlayer->Score += 100;
		} else {
			SnakePlayer *otherPlayer = _players[(~GLBL_Role) & 1];
			otherPlayer->Score += 100;
		}

		Players[0]->Score += _players[0]->Score;
		Players[1]->Score += _players[1]->Score;

		Player *p = new Player();
		p->Score = _currentPlayer->Score;
		p->WinState = _currentPlayer->WinState;
		p->Alive = _currentPlayer->Alive;
		new GameEndView(LCD, Input, CommunicationHandler, p);
	}
}

//update input voor speler
void Snake::UpdatePlayerInput(){
	Input->UpdateInput();

	if(Input->NunchuckAnalogX > 200){
		if(_currentPlayer->Direction != Left)
			_currentPlayer->Direction = Right;
	} else if(Input->NunchuckAnalogY > 200){
		if(_currentPlayer->Direction != Down)
			_currentPlayer->Direction = Up;
	} else if(Input->NunchuckAnalogX < 50){
		if(_currentPlayer->Direction != Right)
			_currentPlayer->Direction = Left;
	} else if(Input->NunchuckAnalogY < 50){
		if(_currentPlayer->Direction != Up)
			_currentPlayer->Direction = Down;
	}
}

//functie voor outputdata, zet waarde van bepaalde actie weg in 'data' en verwerkdit met Doinputdata
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
	
	if(_currentPlayer->Alive == 0)
		data |= SNAKE_LOSE;
	
	DoInputData(data);
	return data;
}

//verwerk data tot actie
void Snake::DoInputData(unsigned char data){
	if(data != 0){
		SnakePlayer *player = _players[data & SNAKE_PLAYERS];

		if((data & SNAKE_LOSE) == SNAKE_LOSE && EndTime == 0){
			player->Alive = 0;
			PlayerCount--;
			EndTime = GameFastTime;
			player->WinState = PL_LOSE;

			return;
		}

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
			player->Draw(LCD);
		}
	}
}

// default destructor
Snake::~Snake()
{
	for(char x = 0; x < MaxX; x++)
		delete[] Grid[x];
	delete[] Grid;
	delete[] _players;
} //~Snake
