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
	_syncCookie = 0;
	_cookies = new Queue<SnakeCookie>(_maxCookies*3);
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
	if(PlayerID == 0 && NewFrame == 0) return;
	Game::Update();
	
	if(EndTime != 0 && EndTime+10 < GameFastTime){
		EndGame();
		return;
	} else if(EndTime != 0){
		return;
	}

	this->CookieTime();
	this->UpdatePlayerInput();
	this->UpdatePlayers();
	this->UpdateCookies();
}

void Snake::EndGame(){
	if(TransitionCounter != 8 && GameFastTime % 2 == 0){
		LCD->fillRect( 20*TransitionCounter,0 ,20,240,RGB(0,0,0));
		LCD->fillRect( 300 - (20 *TransitionCounter),0 ,20,240,RGB(0,0,0));

		TransitionCounter++;
	}else if(TransitionCounter >= 8){
		delete _cookies;
		CurrentView = new GameEndView(LCD, Input, CommunicationHandler, _currentPlayer);
	}
}

void Snake::UpdatePlayers(){
	if(PlayerID == 0){
		CommunicationHandler->Send(GetOutputData());

		if(_syncCookie == 1){
			CommunicationHandler->Send((unsigned char)(_cookie.X/_cookieSize));
			CommunicationHandler->Send((unsigned char)(_cookie.Y/_cookieSize));
			_syncCookie = 0;
		}

		if(PlayerCount > 1)
			DoInputData(CommunicationHandler->Receive());
	} else {
		if(PlayerCount > 1){
			unsigned char receiveData = CommunicationHandler->Receive();
			DoInputData(receiveData);
			
			if((receiveData & SNAKE_SET_COOKIE) > 0){
				unsigned char x = CommunicationHandler->Receive();
				unsigned char y = CommunicationHandler->Receive();
				PlaceCookie((short)x*_cookieSize, (short)y*_cookieSize);
			}
		}
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
	if(PlayerID == 0 && GameSeconds >= _cookieTime && _cookies->Length() < _maxCookies){
		while(1){
			short x = rand() % (32);
			short y = rand() % (24);
			
			if(CheckLocation(x*10, y*10) == 0){
				PlaceCookie(x*10, y*10);
				break;
			}	
		}
		_syncCookie = 1;
		_cookie = _cookies->Peek();
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

void Snake::EatCookie(short x, short y){
	if(_cookies->Length()){
		for(int i = 0; i < _cookies->Length(); i++){
			SnakeCookie cookie = _cookies->Peek(i);
			
			if(cookie.X == x && cookie.Y == y){
				cookie.Time = 0;
				_cookies->Set(i, cookie);
			}
		}
	}
}

void Snake::UpdateCookies(){
	if(_cookies->Length()){
		for(int i = 0; i < _cookies->Length(); i++){
			SnakeCookie cookie = _cookies->Peek(i);
			
			if(cookie.Time <= GameSeconds){
				if(CheckLocation(cookie.X, cookie.Y) == 2)
					LCD->fillCircle(cookie.X+_cookieSize, cookie.Y+_cookieSize, _cookieSize/2, _backgroundColor);
				_cookies->Dequeue();
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

	if(_currentPlayer->PlaceCookie)
		data |= SNAKE_COOKIE;
	
	if(_currentPlayer->Alive == 0)
		data |= SNAKE_LOSE;

	if(_syncCookie == 1)
		data |= SNAKE_SET_COOKIE;
	
	DoInputData(data);
	return data;
}

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

			if(data & SNAKE_COOKIE && player->Size > player->MinSize){
				SnakeQueueData back = player->SnakeQueue->Dequeue();
				player->Size--;
				player->MaxSize--;

				LCD->fillCircle(back.X, back.Y, player->SnakeSize/2, _backgroundColor);
				PlaceCookie(back.X-player->SnakeSize/2, back.Y-player->SnakeSize/2);
				player->PlaceCookie = 0;
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

	if(_cookies->Length()){
		for(int i = 0; i < _cookies->Length(); i++){
			SnakeCookie cookie = _cookies->Peek(i);
			
			if(cookie.X == x && cookie.Y == y && cookie.Time > 0)
				return 2;
		}
	}

	return 0;
}

// default destructor
Snake::~Snake()
{
} //~Snake
