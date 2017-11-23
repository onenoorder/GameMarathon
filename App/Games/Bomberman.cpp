/* 
* Bomberman.cpp
*
* Created: 14-11-2017 14:05:47
* Author: Gerhard
*/

#include "Bomberman.h"


// default constructor
Bomberman::Bomberman(unsigned char ID, MI0283QT9 *LCD, InputController *inputController) : Game(ID, LCD, inputController)
{
	GridBlockSize = 15;
	OffsetX = 16;
	OffsetY = 8;
	MaxX = 19;
	MaxY = 15;
	BombsActiveCount = 0;
	BombStartIndex = 0;
	_bombs = new Queue<BombermanBomb*>();

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
	_LCD->fillScreen(WallColor);
	// Background
	_LCD->fillRect(OffsetX, OffsetY, GridBlockSize * MaxX, GridBlockSize * MaxY, BackgroundColor);

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

	_players[0] = new BombermanPlayer(0, 0, RGB(255, 120, 66), this);
	_players[1] = new BombermanPlayer(MaxX-1, MaxY-1, RGB(255, 120, 66), this);
	
	Grid[_players[0]->X][_players[0]->Y] = 1;
	Grid[_players[1]->X][_players[1]->Y] = 1;

	_players[0]->DrawPlayer(_LCD);
	_players[1]->DrawPlayer(_LCD);

	_currentPlayer = _players[PlayerID];
}

void Bomberman::Update(){
	Game::Update();
	_InputController->UpdateInput();
	_currentPlayer->PlayerUpdated = 0;
	if(_InputController->NunchuckAnalogX > 200){	
		_currentPlayer->Direction = Right;
		_currentPlayer->PlayerUpdated = 1;
	}else if(_InputController->NunchuckAnalogY > 200 ){
		_currentPlayer->Direction = Up;
		_currentPlayer->PlayerUpdated = 1;
	}
	else if(_InputController->NunchuckAnalogX < 50 ){
		_currentPlayer->Direction = Left;
		_currentPlayer->PlayerUpdated = 1;
	}
	else if(_InputController->NunchuckAnalogY < 50){
		_currentPlayer->Direction = Down;
		_currentPlayer->PlayerUpdated = 1;
	}

	if(_InputController->NunchuckZButton && Grid[_currentPlayer->X][_currentPlayer->Y] != Bomb && _currentPlayer->Bombs != _currentPlayer->MaxBombs && _currentPlayer->BombTime +1 < GameTime){
		_currentPlayer->PlaceBomb = 1;
	}

	if(PlayerID == 0){
		/*OutputData = GetOutputData();
		Serial.println(OutputData);
		_master->SendTo(1);
		_master->ReceiveFrom(1);
		DoInputData(InputData);
		Serial.println(InputData);*/
		OutputData = GetOutputData();
		Serial.write(OutputData);

		/*while(!Serial.available());
		InputData = Serial.read();
		DoInputData(InputData);*/
	} else {
		/*OutputData = GetOutputData();
		while(ReceivedData == 0);
		DoInputData(InputData);
		Serial.println(InputData);*/
		
		while(!Serial.available());
		InputData = Serial.read();
		DoInputData(InputData);
		
		OutputData = GetOutputData();
		Serial.write(OutputData);
	}

	if(_bombs->Length()){
		for(int i = 0; i < _bombs->Length(); i++){
			BombermanBomb * bomb = _bombs->Peek(i);	

			if( bomb->TimePlaced+1 == GameTime  && bomb->Ticks == 0 ){
				bomb->Tick(_LCD);
			}
			else if( bomb->TimePlaced+2 == GameTime && bomb->Ticks == 1){
				bomb->Tick(_LCD);
			}
			else if( bomb->TimePlaced+3 == GameTime && bomb->Ticks == 2){
				bomb->Tick(_LCD);
			}
			else if( bomb->TimePlaced+4 <= GameTime && !bomb->Exploding ){
				bomb->Explode(_LCD);
				/*bomb->Exploding = 1;
				char directions = 0x00;
				for (int blast = 0; blast < bomb->Player->Blastpower; blast++)
				{
					if( !(directions & 0x01) && bomb->Y+blast+1 < MaxY && Grid[bomb->X][bomb->Y+blast+1]  != Wall ){
						if(Grid[bomb->X][bomb->Y+blast+1]  == Rock ){
							directions |= 0x01;
						}
						Grid[bomb->X][bomb->Y+blast+1] = Explotion;
						drawGridCell(bomb->X,bomb->Y+blast+1);
					
					}else{
						directions |= 0x01;
					}

					if(!(directions & 0x02) && bomb->Y-blast-1 >= 0 && Grid[bomb->X][bomb->Y-blast-1]  != Wall ){
						if(Grid[bomb->X][bomb->Y-blast-1]  == Rock ){
							directions |= 0x02;
						}
						Grid[bomb->X][bomb->Y-blast-1] = Explotion;
						drawGridCell(bomb->X,bomb->Y-blast-1);
						
					}else{
						directions |= 0x02;
					}

					if(!(directions & 0x04) && bomb->X+blast+1 < MaxX && Grid[bomb->X+blast+1][bomb->Y] != Wall ){
						if(Grid[bomb->X+blast+1][bomb->Y]  == Rock ){
							directions |= 0x04;
						}
						Grid[bomb->X+blast+1][bomb->Y] = Explotion;
						drawGridCell(bomb->X+blast+1,bomb->Y);					
					}else{
						directions |= 0x04;
					}

					if(!(directions & 0x08) && bomb->X-blast-1 >= 0 && Grid[bomb->X-blast-1][bomb->Y] != Wall ){
						if(Grid[bomb->X-blast-1][bomb->Y]  == Rock ){
							directions |= 0x08;
						}
						Grid[bomb->X-blast-1][bomb->Y] = Explotion;
						drawGridCell(bomb->X-blast-1,bomb->Y);					
					}else{
						directions |= 0x08;
					}
				}*/
			}
		}

		// clear bombs
		for(int x = 0; x < _bombs->Length(); x++){
			BombermanBomb * bomb = _bombs->Peek(x);	
			if( bomb->TimePlaced+5 <= GameTime ){
				_bombs->Dequeue();						
				bomb->Player->Bombs--;
				//clear bomb
				Grid[bomb->X][bomb->Y] = Walkable;
				drawGridCell(bomb->X,bomb->Y);

				char directions = 0x00;
				for (int blast = 0; blast < bomb->Player->Blastpower; blast++)
				{
					if(bomb->Y+blast+1 < MaxY && Grid[bomb->X][bomb->Y+blast+1]  == Explotion   ){					
						Grid[bomb->X][bomb->Y+blast+1] = Walkable;
						drawGridCell(bomb->X,bomb->Y+blast+1);
					}

					if(bomb->Y-blast-1 >= 0 && Grid[bomb->X][bomb->Y-blast-1]  == Explotion  ){					
						Grid[bomb->X][bomb->Y-blast-1] = Walkable;
						drawGridCell(bomb->X,bomb->Y-blast-1);
					}

					if(bomb->X+blast+1 < MaxX && Grid[bomb->X+blast+1][bomb->Y] == Explotion ){					
						Grid[bomb->X+blast+1][bomb->Y] = Walkable;
						drawGridCell(bomb->X+blast+1,bomb->Y);
					}

					if(bomb->X-blast-1 >= 0 && Grid[bomb->X-blast-1][bomb->Y] == Explotion  ){					
						Grid[bomb->X-blast-1][bomb->Y] = Walkable;
						drawGridCell(bomb->X-blast-1,bomb->Y);
					}
				}
			}
		}
	}
}

unsigned char Bomberman::GetOutputData(){
	unsigned char data = 0;
	if(_currentPlayer->PlayerUpdated == 1 || _currentPlayer->PlaceBomb == 1){
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
		DoInputData(data);
	}
	return data;
}

void Bomberman::DoInputData(unsigned char data){
	if(data != 0){
		BombermanPlayer *player = _players[data & BOMBERMAN_PLAYERS];

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

		if(data >= BOMBERMAN_PLACE_BOM){
			_bombs->Enqueue( new  BombermanBomb(player->X,player->Y,GameTime, player, BombsActiveCount, this));
			Grid[player->X][player->Y] = Bomb;
			drawGridCell(player->X,player->Y);		
			player->Bombs++;	
			player->BombTime = GameTime;
		}
			
		drawGridCell(player->X, player->Y);
		player->Move();
		player->DrawPlayer(_LCD);
	}
}

void Bomberman::drawGridCell(char x, char y){
	_LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, BackgroundColor);

	if(Grid[x][y] == Wall)
		_LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, WallColor);
	else if(Grid[x][y] == Rock)
		_LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, RockColor);
	else if(Grid[x][y] == Explotion)
		_LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, RGB(255,0,0));
	else if(Grid[x][y] == Walkable)
		_LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, BackgroundColor);
	else if(Grid[x][y] == Bomb){
		_LCD->fillEllipse(OffsetX + x * GridBlockSize + (GridBlockSize/2), OffsetY + y * GridBlockSize + (GridBlockSize/2), GridBlockSize/2, GridBlockSize/2, RGB(0,0,0));
	}	

}


// default destructor
Bomberman::~Bomberman()
{
	delete[] Grid;
} //~Bomberman
