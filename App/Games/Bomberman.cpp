/*
* Bomberman.cpp
*
* Created: 14-11-2017 14:05:47
* Author: Gerhard
*/

#include "Bomberman.h"


// default constructor
Bomberman::Bomberman(unsigned char ID, unsigned char playerCount, MI0283QT9 *LCD, InputController *inputController, Communication *communication) : Game(ID, playerCount, LCD, inputController, communication)
{

	GridBlockSize = 25;
	OffsetX = 16;
	OffsetY = 8;
	MaxX = 9;
	MaxY = 9;
	EndTime = 0;
	_bombs = new Queue<BombermanBomb*>(20);

	// Colors
	WallColor = RGB(24,24,24);
	BackgroundColor = RGB(31, 145, 39);
	RockColor = RGB(85,85,85);

	// Make grid
	Grid = new char*[MaxX];
	for(char x = 0; x < MaxX; x++)
	Grid[x] = new char[MaxY];
} //Bomberman

void Bomberman::Load()
{
	// Border
	LCD->fillScreen(WallColor);
	// Background
	LCD->fillRect(OffsetX, OffsetY, GridBlockSize * MaxX, GridBlockSize * MaxY, BackgroundColor);

	for(char x = 0; x < MaxX; x++){
		for(char y = 0; y < MaxY; y++){
			// Player 1 location
			if(x == 0 && y < 3 || y == 0 && x < 3)
			Grid[x][y] = Walkable;
			// Player 3 location
			else if(x == MaxX - 1 && y < 3 || y == 0 && x > MaxX-4)
			Grid[x][y] = Walkable;
			// Player 4 location
			else if(y == MaxY - 1 && x < 3 || x == 0 && y > MaxY-4)
			Grid[x][y] = Walkable;
			// Player 2 location
			else if(y == MaxY - 1 && x > MaxX - 4 || x == MaxX-1 && y > MaxY-4)
			Grid[x][y] = Walkable;
			// Wall
			else if(x % 2 == 1 && y % 2 == 1)
			Grid[x][y] = Wall;
			// Rock
			else
			Grid[x][y] = Rock;
			
			drawGridCell(x,y);
		}
	}

	_players[0] = new BombermanPlayer(0, 0, RGB(255, 0, 0), this);
	_players[1] = new BombermanPlayer(MaxX-1, MaxY-1, RGB(0, 0, 255), this);
	
	Grid[_players[0]->X][_players[0]->Y] = 1;
	Grid[_players[1]->X][_players[1]->Y] = 1;

	_players[0]->DrawPlayer(LCD);
	_players[1]->DrawPlayer(LCD);

	_currentPlayer = _players[PlayerID];
	Loaded = 1;
}

void Bomberman::Update(){
	if(PlayerID == 0 && NewFrame == 0) return;
	Game::Update();

	if(EndTime != 0 && EndTime+4 < GameSeconds){
		// TODO remove pointers
		CurrentView = new SelectGameView(LCD, Input, CommunicationHandler);
		return;
	}
	this->UpdatePlayerInput();
	this->UpdatePlayers();
	this->UpdateBombs();
}

void Bomberman::UpdatePlayers(){
	// stop send/recieve 1 second before end of game
	if((EndTime != 0 && EndTime+3 < GameSeconds)) return;

	if(PlayerID == 0){
		CommunicationHandler->Send(GetOutputData());

		if(PlayerCount > 1)
			DoInputData(CommunicationHandler->Receive());
	} else {
		if(PlayerCount > 1  )
			DoInputData(CommunicationHandler->Receive());

		CommunicationHandler->Send(GetOutputData());
	}
}

void Bomberman::UpdatePlayerInput(){
	Input->UpdateInput();

	if(_currentPlayer->Alive == 1 && Grid[_currentPlayer->X][_currentPlayer->Y] == Explotion){
		_currentPlayer->Alive = 0;
		EndTime = GameSeconds;
		Grid[_currentPlayer->X][_currentPlayer->Y] = Grave;
		drawGridCell(_currentPlayer->X,_currentPlayer->Y);
	}

	if(_currentPlayer->Alive == 0) return;
	
	_currentPlayer->PlayerUpdated = 0;
	if(Input->NunchuckAnalogX > 200){
		_currentPlayer->Direction = Right;
		_currentPlayer->PlayerUpdated = 1;
		}else if(Input->NunchuckAnalogY > 200 ){
		_currentPlayer->Direction = Up;
		_currentPlayer->PlayerUpdated = 1;
	}
	else if(Input->NunchuckAnalogX < 50 ){
		_currentPlayer->Direction = Left;
		_currentPlayer->PlayerUpdated = 1;
	}
	else if(Input->NunchuckAnalogY < 50){
		_currentPlayer->Direction = Down;
		_currentPlayer->PlayerUpdated = 1;
	}

	if(Input->NunchuckZButton && Grid[_currentPlayer->X][_currentPlayer->Y] != Bomb && _currentPlayer->Bombs != _currentPlayer->MaxBombs && _currentPlayer->BombTime +1 < GameSeconds){
		_currentPlayer->PlaceBomb = 1;
	}
}

void Bomberman::UpdateBombs(){
	if(_bombs->Length()){
		for(int i = 0; i < _bombs->Length(); i++){
			BombermanBomb * bomb = _bombs->Peek(i);

			if(bomb->TimePlaced+1 == GameSeconds  && bomb->Ticks == 0 ){
				bomb->Tick(LCD);
				} else if(bomb->TimePlaced+2 == GameSeconds && bomb->Ticks == 1){
				bomb->Tick(LCD);
				} else if(bomb->TimePlaced+3 == GameSeconds && bomb->Ticks == 2){
				bomb->Tick(LCD);
				} else if(bomb->TimePlaced+4 <= GameSeconds && !bomb->Exploding ){
				bomb->Explode(LCD);
			}
		}

		// clear bombs
		for(int x = 0; x < _bombs->Length(); x++){
			BombermanBomb * bomb = _bombs->Peek(x);
			if( bomb->TimePlaced+5 <= GameSeconds ){
				_bombs->Dequeue();
				bomb->Player->Bombs--;

				//clear bomb
				if(Grid[bomb->X][bomb->Y] != Grave){
					Grid[bomb->X][bomb->Y] = Walkable;
					drawGridCell(bomb->X,bomb->Y);
				}

				char directions = 0x00;
				for (int blast = 0; blast < bomb->Player->Blastpower; blast++)
				{
					if(bomb->Y+blast+1 < MaxY && Grid[bomb->X][bomb->Y+blast+1]  == Explotion   ){
						if(Grid[bomb->X][bomb->Y+blast+1] != Grave){
							Grid[bomb->X][bomb->Y+blast+1] = Walkable;
							drawGridCell(bomb->X,bomb->Y+blast+1);
						}
					}

					if(bomb->Y-blast-1 >= 0 && Grid[bomb->X][bomb->Y-blast-1]  == Explotion  ){
						if(Grid[bomb->X][bomb->Y+blast-1] != Grave){
							Grid[bomb->X][bomb->Y-blast-1] = Walkable;
							drawGridCell(bomb->X,bomb->Y-blast-1);
						}
					}

					if(bomb->X+blast+1 < MaxX && Grid[bomb->X+blast+1][bomb->Y] == Explotion ){
						if(Grid[bomb->X+blast+1][bomb->Y] != Grave){
							Grid[bomb->X+blast+1][bomb->Y] = Walkable;
							drawGridCell(bomb->X+blast+1,bomb->Y);
						}
					}

					if(bomb->X-blast-1 >= 0 && Grid[bomb->X-blast-1][bomb->Y] == Explotion  ){
						if(Grid[bomb->X+blast-1][bomb->Y] != Grave){
							Grid[bomb->X-blast-1][bomb->Y] = Walkable;
							drawGridCell(bomb->X-blast-1,bomb->Y);
						}
					}
				}
			}
		}
	}
}

unsigned char Bomberman::GetOutputData(){
	unsigned char data = 0;
	if(_currentPlayer->PlayerUpdated == 1 || _currentPlayer->PlaceBomb == 1|| _currentPlayer->Alive == 0){
		data = PlayerID;
		if(_currentPlayer->PlayerUpdated == 1){
			switch(_currentPlayer->Direction){
				case Up:
				data |= BOMBERMAN_MOVE_UP;
				break;
				case Left:
				data |= BOMBERMAN_MOVE_LEFT;
				break;
				case Right:
				data |= BOMBERMAN_MOVE_RIGHT;
				break;
				case Down:
				data |= BOMBERMAN_MOVE_DOWN;
				break;
			};
		}
		if(_currentPlayer->PlaceBomb == 1){
			data |= BOMBERMAN_PLACE_BOM;
			_currentPlayer->PlaceBomb = 0;
		}
		if(_currentPlayer->Alive == 0){
			data |= BOMBERMAN_LOSE;
		}
		DoInputData(data);
	}
	return data;
}

void Bomberman::DoInputData(unsigned char data){
	if(data != 0){
		BombermanPlayer *player = _players[data & BOMBERMAN_PLAYERS];

		if((data & BOMBERMAN_LOSE) == BOMBERMAN_LOSE ){
			player->Alive = 0;
			EndTime = GameSeconds;
			Grid[player->X][player->Y] = Grave;
			drawGridCell(player->X,player->Y);
		}

		if((data & BOMBERMAN_ACTIONS) > 0){
			switch(data & BOMBERMAN_ACTIONS){
				case BOMBERMAN_MOVE_UP:
				player->Direction = Up;
				break;
				case BOMBERMAN_MOVE_LEFT:
				player->Direction = Left;
				break;
				case BOMBERMAN_MOVE_RIGHT:
				player->Direction = Right;
				break;
				case BOMBERMAN_MOVE_DOWN:
				player->Direction = Down;
				break;
			};
			drawGridCell(player->X, player->Y);
			player->Move();
			player->DrawPlayer(LCD);
		}

		if(data >= BOMBERMAN_PLACE_BOM){
			_bombs->Enqueue(new  BombermanBomb(player->X,player->Y,GameSeconds, player, this));
			Grid[player->X][player->Y] = Bomb;
			drawGridCell(player->X,player->Y);
			player->Bombs++;
			player->BombTime = GameSeconds;

			drawGridCell(player->X, player->Y);
			player->DrawPlayer(LCD);
		}	
	}
}

void Bomberman::drawGridCell(char x, char y){
	LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, BackgroundColor);

	if(Grid[x][y] == Wall)
	LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, WallColor);
	else if(Grid[x][y] == Rock)
	LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, RockColor);
	else if(Grid[x][y] == Explotion)
	LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, RGB(255,0,0));
	else if(Grid[x][y] == Walkable)
	LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, BackgroundColor);
	else if(Grid[x][y] == Bomb)
	LCD->fillEllipse(OffsetX + x * GridBlockSize + (GridBlockSize/2), OffsetY + y * GridBlockSize + (GridBlockSize/2), GridBlockSize/2, GridBlockSize/2, RGB(0,0,0));
	else if(Grid[x][y] == Grave)
	LCD->fillEllipse(OffsetX + x * GridBlockSize + (GridBlockSize/2), OffsetY + y * GridBlockSize + (GridBlockSize/2), GridBlockSize/2, GridBlockSize/2, RGB(255,255,255));
	


}


// default destructor
Bomberman::~Bomberman()
{
	delete[] Grid;
} //~Bomberman
