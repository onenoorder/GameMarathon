/* 
* RockPaperScissors.cpp
*
* Created: 27-12-2017 17:58:12
* Author: Gerhard
*/

#include "RockPaperScissors.h"

// default constructor
RockPaperScissors::RockPaperScissors(MI0283QT9 *LCD, InputController *inputController, Communication *communication) : Game(LCD, inputController, communication)
{
	BackgroundColor = RGB(66, 244, 95);
	_turn = 0;
} //RockPaperScissors

void RockPaperScissors::Load()
{
	// Background
	LCD->fillScreen(BackgroundColor);

	_players[0] = new RockPaperScissorsPlayer(0, RGB(255,0,0), this);
	_players[1] = new RockPaperScissorsPlayer(1, RGB(0,0,255), this);

	_currentPlayer = _players[PlayerID];

	_turnTime = GameSeconds + 3;

	Loaded = 1;
}

void RockPaperScissors::Update(){
	if(PlayerID == 0 && NewFrame == 0) return;
	Game::Update();

	if(_turn > 3){
		EndGame();
		return;
	}

	this->UpdatePlayerInput();
	this->UpdatePlayers();

	if(_turnTime <= GameSeconds){
		_players[0]->Draw(LCD);
		_players[1]->Draw(LCD);

		if(_players[0]->Direction == Up && _players[1]->Direction != Left)
			_players[0]->Score += 100;
		else if(_players[0]->Direction == Left && _players[1]->Direction != Right)
			_players[0]->Score += 100;
		else if(_players[0]->Direction == Right && _players[1]->Direction != Up)
			_players[0]->Score += 100;
		else
			_players[1]->Score += 100;

		_turn++;
		_turnTime += 3;
	} else {
		_currentPlayer->Draw(LCD);
	}
}

void RockPaperScissors::EndGame(){
	if(_players[0]->Score == _players[1]->Score){
		_turn--;
		return;
	}

	Players[0]->Score += _players[0]->Score;
	Players[1]->Score += _players[1]->Score;

	_players[0]->WinState = _players[0]->Score > _players[1]->Score ? PL_WIN : PL_LOSE;
	_players[1]->WinState = _players[1]->Score > _players[0]->Score ? PL_WIN : PL_LOSE;

	Player *p = new Player();
	p->Score = _currentPlayer->Score;
	p->WinState = _currentPlayer->WinState;
	p->Alive = _currentPlayer->Alive;
	new GameEndView(LCD, Input, CommunicationHandler, p);
}

//update input voor speler
void RockPaperScissors::UpdatePlayerInput(){
	Input->UpdateInput();

	if(Input->NunchuckAnalogX > 200)
		_currentPlayer->Direction = Right;
	else if(Input->NunchuckAnalogY > 200)
		_currentPlayer->Direction = Up;
	else if(Input->NunchuckAnalogX < 50)
		_currentPlayer->Direction = Left;
}

//functie voor outputdata, zet waarde van bepaalde actie weg in 'data' en verwerkdit met Doinputdata
unsigned char RockPaperScissors::GetOutputData(){
	unsigned char data = 0;
	data = PlayerID;
	switch(_currentPlayer->Direction){
		case Up:
			data |= ROCKPAPERSCISSORS_ROCK;
			break;
		case Left:
			data |= ROCKPAPERSCISSORS_PAPER;
			break;
		case Right:
			data |= ROCKPAPERSCISSORS_SCISSORS;
			break;
	};
	
	if(_currentPlayer->Alive == 0)
		data |= ROCKPAPERSCISSORS_LOSE;
	
	DoInputData(data);
	return data;
}

//verwerk data tot actie
void RockPaperScissors::DoInputData(unsigned char data){
	if(data != 0){
		RockPaperScissorsPlayer *player = _players[data & ROCKPAPERSCISSORS_PLAYERS];

		if((data & ROCKPAPERSCISSORS_LOSE) == ROCKPAPERSCISSORS_LOSE && EndTime == 0){
			player->Alive = 0;
			PlayerCount--;
			EndTime = GameFastTime;
			player->WinState = PL_LOSE;

			return;
		}

		if((data & ROCKPAPERSCISSORS_ACTIONS) > 0){
			switch(data & ROCKPAPERSCISSORS_ACTIONS){
				case ROCKPAPERSCISSORS_ROCK:
					player->Direction = Up;
					break;
				case ROCKPAPERSCISSORS_PAPER:
					player->Direction = Left;
					break;
				case ROCKPAPERSCISSORS_SCISSORS:
					player->Direction = Right;
					break;
			};
		}
	}
}

// default destructor
RockPaperScissors::~RockPaperScissors()
{
	delete[] _players;
} //~RockPaperScissors
