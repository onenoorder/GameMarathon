/*
* Bomberman.cpp
*
* Created: 14-11-2017 14:05:47
* Author: Gerhard
*/

#include "Bomberman.h"

// default constructor
Bomberman::Bomberman(MI0283QT9 *LCD, InputController *inputController, Communication *communication) : Game(LCD, inputController, communication)
{
	GridBlockSize = 25;
	OffsetX = 22;
	OffsetY = 8;
	MaxX = 11;
	MaxY = 9;
	_bombs = new Queue<BombermanBomb*>(20);
	// Colors
	WallColor = RGB(65,65,65);
	BackgroundColor = RGB(12, 103, 37);
	RockColor = RGB(85,85,85);
	RockGlowColor = RGB(105, 105, 105);
	ExplotionColor = RGB(240, 50, 1);
	ExplotionTextColor = RGB(204, 24, 27);

	// Make grid
	Grid = new char*[MaxX];
	for(char x = 0; x < MaxX; x++)
		Grid[x] = new char[MaxY];
} //Bomberman

//laad nieuw bomberman spel
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
			// PowerUp more bombs
			else if(x == 2 && y == 2 || x == MaxX-3 && y == 2 || x == 2 && y == MaxY-3 || x == MaxX-3 && y == MaxY-3)
				Grid[x][y] = MoreBombs | Rock;
			// PowerUp more power
			else if(x % 2 == 0 && y % 2 == 0)
				Grid[x][y] = MorePower | Rock;
			// Rock
			else
				Grid[x][y] = Rock;
				
			DrawGridCell(x,y);
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

//bomberman updaten
void Bomberman::Update(){
	if(PlayerID == 0 && NewFrame == 0) return;
	Game::Update();

	if(EndTime != 0 && EndTime+10 < GameFastTime){
		EndGame();
		return;
	}
	this->UpdatePlayerInput();
	this->UpdatePlayers();
	this->UpdateBombs();
}

//wanneer timer voorbij is, laad eindscherm
void Bomberman::EndGame(){
	if(TransitionCounter != 8 && GameFastTime % 2 == 0){
		LCD->fillRect(20*TransitionCounter,0 ,20,240,RGB(0,0,0));
		LCD->fillRect(300 - (20 *TransitionCounter),0 ,20,240,RGB(0,0,0));

		TransitionCounter++;
	} else if(TransitionCounter >= 8){
		if(_currentPlayer->WinState == PL_WIN){
			_currentPlayer->Score += 100;
		} else {
			BombermanPlayer *otherPlayer = _players[(~GLBL_Role) & 1];
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

//update input
void Bomberman::UpdatePlayerInput(){
	Input->UpdateInput();

	if(_currentPlayer->Alive == 1 && Grid[_currentPlayer->X][_currentPlayer->Y] >= Explotion && Grid[_currentPlayer->X][_currentPlayer->Y] <= Explotion_3+2 && EndTime == 0){
		_currentPlayer->Alive = 0;
		PlayerCount--;
		EndTime = GameFastTime;
		Grid[_currentPlayer->X][_currentPlayer->Y] = Grave;
		_currentPlayer->WinState = PL_LOSE;
		DrawGridCell(_currentPlayer->X,_currentPlayer->Y);
	}

	if(_currentPlayer->Alive == 0) return;
	
	_currentPlayer->PlayerUpdated = 0;

	if(Input->NunchuckAnalogX > 200){
		_currentPlayer->Direction = Right;
		_currentPlayer->PlayerUpdated = 1;
		}else if(Input->NunchuckAnalogY > 200){
		_currentPlayer->Direction = Up;
		_currentPlayer->PlayerUpdated = 1;
	}
	else if(Input->NunchuckAnalogX < 50){
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
//udate de bommen
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
			} else if(bomb->TimePlaced+4 == GameSeconds && !bomb->Exploding){
				bomb->Explode(LCD, 0);
			} else if(bomb->TimePlaced+5 == GameSeconds){
				bomb->Explode(LCD, 1);
			} else if(bomb->TimePlaced+6 == GameSeconds){
				bomb->Explode(LCD, 2);
			}
		}

		// clear bombs
		for(int x = 0; x < _bombs->Length(); x++){
			BombermanBomb * bomb = _bombs->Peek(x);
			if(bomb->TimePlaced+7 <= GameSeconds){
				_bombs->Dequeue();
				bomb->Player->Bombs--;

				//clear bomb
				if(Grid[bomb->X][bomb->Y] != Grave){
					Grid[bomb->X][bomb->Y] = Walkable;
					DrawGridCell(bomb->X,bomb->Y);
				}

				char directions = 0x00;
				for (int blast = 0; blast < bomb->Player->Blastpower; blast++)
				{
					if(bomb->Y+blast+1 < MaxY && Grid[bomb->X][bomb->Y+blast+1] >= Explotion && Grid[bomb->X][bomb->Y+blast+1] <= Explotion_3+2){
						if(Grid[bomb->X][bomb->Y+blast+1] != Grave){
							Grid[bomb->X][bomb->Y+blast+1] = Walkable;
							DrawGridCell(bomb->X,bomb->Y+blast+1);
						}
					}

					if(bomb->Y-blast-1 >= 0 && Grid[bomb->X][bomb->Y-blast-1] >= Explotion && Grid[bomb->X][bomb->Y-blast-1] <= Explotion_3+2){
						if(Grid[bomb->X][bomb->Y-blast-1] != Grave){
							Grid[bomb->X][bomb->Y-blast-1] = Walkable;
							DrawGridCell(bomb->X,bomb->Y-blast-1);
						}
					}

					if(bomb->X+blast+1 < MaxX && Grid[bomb->X+blast+1][bomb->Y] >= Explotion && Grid[bomb->X+blast+1][bomb->Y] <= Explotion_3+2){
						if(Grid[bomb->X+blast+1][bomb->Y] != Grave){
							Grid[bomb->X+blast+1][bomb->Y] = Walkable;
							DrawGridCell(bomb->X+blast+1,bomb->Y);
						}
					}

					if(bomb->X-blast-1 >= 0 && Grid[bomb->X-blast-1][bomb->Y] >= Explotion && Grid[bomb->X-blast-1][bomb->Y] <= Explotion_3+2){
						if(Grid[bomb->X-blast-1][bomb->Y] != Grave){
							Grid[bomb->X-blast-1][bomb->Y] = Walkable;
							DrawGridCell(bomb->X-blast-1,bomb->Y);
						}
					}
				}
			}
		}
	}
}
//functie voor ouptutdata, zet waarde van bepaalde actie in 'data'
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

//verwerk input tot actie,
void Bomberman::DoInputData(unsigned char data){
	if(data != 0){
		BombermanPlayer *player = _players[data & BOMBERMAN_PLAYERS];

		if((data & BOMBERMAN_LOSE) == BOMBERMAN_LOSE && EndTime == 0){
			player->Alive = 0;
			PlayerCount--;
			player->PlayerUpdated = 0;
			EndTime = GameFastTime;
			Grid[player->X][player->Y] = Grave;

			DrawGridCell(player->X,player->Y);
			return;
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
			DrawGridCell(player->X, player->Y);
			player->Move();
			player->DrawPlayer(LCD);
		}

		if(data >= BOMBERMAN_PLACE_BOM){
			_bombs->Enqueue(new  BombermanBomb(player->X,player->Y,GameSeconds, player, this));
			Grid[player->X][player->Y] = Bomb;
			DrawGridCell(player->X,player->Y);		
			player->Bombs++;
			player->BombTime = GameSeconds;

			DrawGridCell(player->X, player->Y);
			player->DrawPlayer(LCD);
			player->Score += 50;
		}
	}
}
//teken individuele cel, wordt aangeroepen in "load" op basis van locatie op map.
void Bomberman::DrawGridCell(char x, char y){
	LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, BackgroundColor);

	if(Grid[x][y] == Wall) {
		LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, WallColor);

		// Outerlines
		LCD->drawLine(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, OffsetX + x * GridBlockSize + GridBlockSize-1, OffsetY + y * GridBlockSize, RockGlowColor);
		LCD->drawLine(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize + GridBlockSize-1, OffsetX + x * GridBlockSize + GridBlockSize-1, OffsetY + y * GridBlockSize + GridBlockSize-1, RockGlowColor);
		LCD->drawLine(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize + GridBlockSize-1, RockGlowColor);
		LCD->drawLine(OffsetX + x * GridBlockSize + GridBlockSize-1, OffsetY + y * GridBlockSize, OffsetX + x * GridBlockSize + GridBlockSize-1, OffsetY + y * GridBlockSize + GridBlockSize-1, RockGlowColor);
	} else if((Grid[x][y] & Rock) > 0) {
		LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, RockColor);

		// Outerlines
		LCD->drawLine(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, OffsetX + x * GridBlockSize + GridBlockSize-1, OffsetY + y * GridBlockSize, WallColor);
		LCD->drawLine(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize + GridBlockSize-1, OffsetX + x * GridBlockSize + GridBlockSize-1, OffsetY + y * GridBlockSize + GridBlockSize-1, WallColor);
		LCD->drawLine(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize + GridBlockSize-1, WallColor);
		LCD->drawLine(OffsetX + x * GridBlockSize + GridBlockSize-1, OffsetY + y * GridBlockSize, OffsetX + x * GridBlockSize + GridBlockSize-1, OffsetY + y * GridBlockSize + GridBlockSize-1, WallColor);

		// Innerlines
		LCD->drawLine(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize + (GridBlockSize/3), OffsetX + x * GridBlockSize + GridBlockSize-1, OffsetY + y * GridBlockSize + (GridBlockSize/3), WallColor);
		LCD->drawLine(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize + (GridBlockSize/3)*2, OffsetX + x * GridBlockSize + GridBlockSize-1, OffsetY + y * GridBlockSize + (GridBlockSize/3)*2, WallColor);

		LCD->drawLine(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize + 1, OffsetX + x * GridBlockSize + GridBlockSize-1, OffsetY + y * GridBlockSize + 1, RockGlowColor);
		LCD->drawLine(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize + (GridBlockSize/3)+1, OffsetX + x * GridBlockSize + GridBlockSize-1, OffsetY + y * GridBlockSize + (GridBlockSize/3)+1, RockGlowColor);
		LCD->drawLine(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize + (GridBlockSize/3)*2+1, OffsetX + x * GridBlockSize + GridBlockSize-1, OffsetY + y * GridBlockSize + (GridBlockSize/3)*2+1, RockGlowColor);

		// Stones
		LCD->drawLine(OffsetX + x * GridBlockSize + (GridBlockSize/4), OffsetY + y * GridBlockSize, OffsetX + x * GridBlockSize + (GridBlockSize/4), OffsetY + y * GridBlockSize + (GridBlockSize/3), WallColor);
		LCD->drawLine(OffsetX + x * GridBlockSize + (GridBlockSize/4)*2, OffsetY + y * GridBlockSize + (GridBlockSize/3), OffsetX + x * GridBlockSize + (GridBlockSize/4)*2, OffsetY + y * GridBlockSize + (GridBlockSize/3)*2, WallColor);
		LCD->drawLine(OffsetX + x * GridBlockSize + (GridBlockSize/4)*3, OffsetY + y * GridBlockSize + (GridBlockSize/3)*2, OffsetX + x * GridBlockSize + (GridBlockSize/4)*3, OffsetY + y * GridBlockSize + GridBlockSize-1, WallColor);
	} else if(Grid[x][y] >= Explotion_1 && Grid[x][y] <= Explotion_1+2) {
		if((Grid[x][y] & 3) == 0){
			LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, ExplotionTextColor);
		} else if((Grid[x][y] & 1) == 1){
			LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, ExplotionColor);
			LCD->drawText(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, "B", ExplotionTextColor, ExplotionColor, GridBlockSize/7);
		} else {
			LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, BackgroundColor);
			LCD->drawText(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, "B", ExplotionColor, BackgroundColor, GridBlockSize/7);
		}
	} else if(Grid[x][y] >= Explotion_2 && Grid[x][y] <= Explotion_2+2) {
		if((Grid[x][y] & 3) == 0){
			LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, ExplotionTextColor);
		} else if((Grid[x][y] & 1) == 1){
			LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, ExplotionColor);
			LCD->drawText(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, "I", ExplotionTextColor, ExplotionColor, GridBlockSize/7);
		} else {
			LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, BackgroundColor);
			LCD->drawText(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, "I", ExplotionColor, BackgroundColor, GridBlockSize/7);
		}
	} else if(Grid[x][y] >= Explotion_3 && Grid[x][y] <= Explotion_3+2) {
		if(Grid[x][y] == Explotion_3){
			LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, ExplotionTextColor);
		} else if((Grid[x][y] & 1) == 1){
			LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, ExplotionColor);
			LCD->drawText(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, "E", ExplotionTextColor, ExplotionColor, GridBlockSize/7);
		} else {
			LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, BackgroundColor);
			LCD->drawText(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, "E", ExplotionColor, BackgroundColor, GridBlockSize/7);
		}
	} else if(Grid[x][y] >= Explotion && Grid[x][y] <= Explotion+2) {
		if((Grid[x][y] & 3) == 0){
			LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, ExplotionTextColor);
		} else if((Grid[x][y] & 1) == 1){
			LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, ExplotionColor);
			LCD->drawText(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, "M", ExplotionTextColor, ExplotionColor, GridBlockSize/7);
		} else {
			LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, BackgroundColor);
			LCD->drawText(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, "M", ExplotionColor, BackgroundColor, GridBlockSize/7);
		}
	} else if(Grid[x][y] == Walkable){
		LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, BackgroundColor);
	} else if(Grid[x][y] == Bomb){
		LCD->fillEllipse(OffsetX + x * GridBlockSize + (GridBlockSize/2), OffsetY + y * GridBlockSize + (GridBlockSize/2), GridBlockSize/2, GridBlockSize/2, RGB(0,0,0));
		LCD->fillEllipse(OffsetX + x * GridBlockSize + (GridBlockSize/2), OffsetY + y * GridBlockSize + (GridBlockSize/4), GridBlockSize/4, GridBlockSize/4, RockColor);
	} else if(Grid[x][y] == Grave){
		LCD->fillEllipse(OffsetX + x * GridBlockSize + (GridBlockSize/2), OffsetY + y * GridBlockSize + (GridBlockSize/2), GridBlockSize/2, GridBlockSize/2, RGB(255,255,255));
	} else if(Grid[x][y] == MorePower){
		LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, RGB(0,0,255));
		LCD->drawText(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, "P", RGB(255,255,0), RGB(0,0,255), GridBlockSize/7);
	} else if(Grid[x][y] == MoreBombs){
		LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, RGB(0,0,255));
		LCD->drawText(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, "B", RGB(255,255,0), RGB(0,0,255), GridBlockSize/7);
	}
}

// default destructor
Bomberman::~Bomberman()
{
	for(char x = 0; x < MaxX; x++)
		delete[] Grid[x];
	delete[] Grid;
	delete _bombs;
	delete[] _players;
} //~Bomberman
