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
	
	_biggerDelay = 5;
	_bigger = 0;
	_biggerTime = GameSeconds + _biggerDelay;
} //Snake

//snakespel laden
void Snake::Load()
{
	// Background
	LCD->fillScreen(_backgroundColor);

	_players[0] = new SnakePlayer(5,5, RGB(255,0,0), this);
	_players[0]->Direction = Right;
	_playerCount++;
	_players[1] = new SnakePlayer(315,235, RGB(0,0,255), this);
	_players[1]->Direction = Left;
	_playerCount++;

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

	this->BiggerTime();
	this->UpdatePlayerInput();
	this->UpdatePlayers();
}

//afgelopen spel spel eindigen
void Snake::EndGame(){
	if(TransitionCounter != 8 && GameFastTime % 2 == 0){
		LCD->fillRect( 20*TransitionCounter,0 ,20,240,RGB(0,0,0));
		LCD->fillRect( 300 - (20 *TransitionCounter),0 ,20,240,RGB(0,0,0));

		TransitionCounter++;
	}else if(TransitionCounter >= 8){
		CurrentView = new GameEndView(LCD, Input, CommunicationHandler, _currentPlayer);
	}
}

//updaten speler
void Snake::UpdatePlayers(){
	if(PlayerID == 0){
		CommunicationHandler->Send(GetOutputData());

		if(PlayerCount > 1)
			DoInputData(CommunicationHandler->Receive());
	} else {
		if(PlayerCount > 1){
			unsigned char receiveData = CommunicationHandler->Receive();
			DoInputData(receiveData);
			
			if((receiveData & SNAKE_BIGGER) > 0){
				_bigger = 1;
			}
		}
		CommunicationHandler->Send(GetOutputData());
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

//
void Snake::BiggerTime(){
	if(PlayerID == 0 && GameSeconds >= _biggerTime && _currentPlayer->MaxSize < _currentPlayer->SnakeSize){
		_bigger = 1;
		_biggerTime = GameSeconds + _biggerDelay;
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

	if(_bigger == 1){
		data |= SNAKE_BIGGER;
		_bigger = 0;
	}
	
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
			_currentPlayer->WinState = PL_WIN;
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

			if(data & SNAKE_BIGGER && player->MaxSize < player->SnakeSize){
				player->MaxSize++;
			}
			player->Move();
			player->Draw(LCD);
		}
	}
}



unsigned char Snake::CheckLocation(short x, short y){
	for(int p = 0; p < _playerCount; p++){
		if(_players[p]->SnakeQueue->Length()){
			for(int i = 0; i < _players[p]->SnakeQueue->Length(); i++){
				SnakeQueueData snakeQueueData = _players[p]->SnakeQueue->Peek(i);
				
				if(snakeQueueData.X-(_players[p]->SnakeSize/2) == x && snakeQueueData.Y-(_players[p]->SnakeSize/2) == y)
					return 1;
			}
		}
	}
	return 0;
}

// default destructor
Snake::~Snake()
{
} //~Snake
