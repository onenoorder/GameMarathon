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
	
	_cookieTime = 0;
	_cookieSize = 5;
	_cookieColor = RGB(244,176,66);
	_maxCookies = 10;
	_cookieDelay = 5;
	_cookies = new Queue<SnakeCookie>(_maxCookies*5);
} //Snake

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

void Snake::Update(){
	Game::Update();

	
	this->CookieTime();
	this->UpdatePlayerInput();
	this->UpdatePlayers();
	this->UpdateCookies();
}

void Snake::UpdatePlayers(){
	if(PlayerID == 0){
		CommunicationHandler->Send(GetOutputData());

		if(PlayerCount > 1)
			DoInputData(CommunicationHandler->Receive());
	} else {
		if(PlayerCount > 1)
			DoInputData(CommunicationHandler->Receive());

		CommunicationHandler->Send(GetOutputData());
	}
}

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

	if(Input->NunchuckZButton && _currentPlayer->SnakeQueue->Length() != 2){
		_currentPlayer->PlaceCookie = 1;
	}
}

void Snake::CookieTime(){
	if(GameSeconds >= _cookieTime && _cookies->Length() < _maxCookies){
		while(1){
			short x = rand() % (32);
			short y = rand() % (24);
			
			if(CheckLocation(x*10, y*10) == 0){
				PlaceCookie(x*10, y*10);
				break;
			}	
		}
		_cookieTime = GameSeconds + _cookieDelay;
	}
}

void Snake::PlaceCookie(short x, short y){
	if(_cookies->Length() < _maxCookies*5){
		SnakeCookie cookie = {x, y, GameSeconds + (_cookieDelay*_maxCookies)};
		LCD->fillCircle(cookie.X+_cookieSize, cookie.Y+_cookieSize, _cookieSize/2, _cookieColor);
		_cookies->Enqueue(cookie);
	}
}

void Snake::UpdateCookies(){
	if(_cookies->Length()){
		for(int i = 0; i < _cookies->Length(); i++){
			SnakeCookie cookie = _cookies->Peek(i);
			
			if(cookie.Time <= GameSeconds){
				_cookies->Dequeue();
				LCD->fillCircle(cookie.X+_cookieSize, cookie.Y+_cookieSize, _cookieSize/2, _backgroundColor);
			}
		}
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

	if(_currentPlayer->PlaceCookie){
		SnakeQueueData back = _currentPlayer->SnakeQueue->Dequeue();
		_currentPlayer->Size--;
		_currentPlayer->MaxSize--;

		LCD->fillCircle(back.X, back.Y, _currentPlayer->SnakeSize/2, _backgroundColor);
		PlaceCookie(back.X-_currentPlayer->SnakeSize/2, back.Y-_currentPlayer->SnakeSize/2);
		_currentPlayer->PlaceCookie = 0;
	}
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
			player->Draw(LCD);
		}
	}
}

unsigned char Snake::CheckLocation(short x, short y){
	for(int p = 0; p < _playerCount; p++){
		if(_players[p]->SnakeQueue->Length()){
			for(int i = 0; i < _players[p]->SnakeQueue->Length(); i++){
				SnakeQueueData snakeQueueData = _players[p]->SnakeQueue->Peek(i);
				
				if(snakeQueueData.X == x && snakeQueueData.Y == y)
					return 1;
			}
		}
	}

	if(_cookies->Length()){
		for(int i = 0; i < _cookies->Length(); i++){
			SnakeCookie cookie = _cookies->Peek(i);
			
			if(cookie.X == x && cookie.Y == y)
				return 2;
		}
	}

	return 0;

	_currentPlayer->Move();
	_currentPlayer->Draw(LCD);
	_players[1]->Move();
	_players[1]->Draw(LCD);
	_delay_ms(100);

}

// default destructor
Snake::~Snake()
{
} //~Snake
