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
	if(_currentPlayer->PlayerUpdated){
			drawGridCell(_currentPlayer->X,_currentPlayer->Y);
			_currentPlayer->Move();
			_currentPlayer->DrawPlayer(_LCD);
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

		while(!Serial.available());
		InputData = Serial.read();
		DoInputData(InputData);
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

	if(_InputController->NunchuckZButton && Grid[_currentPlayer->X][_currentPlayer->Y] != Bomb && _currentPlayer->Bombs != _currentPlayer->MaxBombs){
		Serial.println("Bomb!");
		_bombs->Enqueue( new  BombermanBomb(_currentPlayer->X,_currentPlayer->Y,GameTime, _currentPlayer, BombsActiveCount));
		Grid[_currentPlayer->X][_currentPlayer->Y] = Bomb;
		drawGridCell(_currentPlayer->X,_currentPlayer->Y);		
		_currentPlayer->Bombs++;	
	}

	while(1){
		BombermanBomb * bomb = _bombs->Peek();
		
		if( bomb->TimePlaced+3 <= GameTime ){
			bomb = _bombs->Dequeue();
			bomb->Player->Bombs--;
			//explode
			Grid[bomb->X][bomb->Y] = Walkable;
			Grid[bomb->X][bomb->Y+1] = Walkable;
			Grid[bomb->X][bomb->Y-1] = Walkable;
			Grid[bomb->X+1][bomb->Y] = Walkable;
			Grid[bomb->X-1][bomb->Y] = Walkable;

			drawGridCell(bomb->X,bomb->Y);
			drawGridCell(bomb->X,bomb->Y+1);
			drawGridCell(bomb->X,bomb->Y-1);
			drawGridCell(bomb->X+1,bomb->Y);
			drawGridCell(bomb->X-1,bomb->Y);		
		}else{
			break;
		}
	}
}

unsigned char Bomberman::GetOutputData(){
	// TODO:if player moved?
	unsigned char data = PlayerID;
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
		// TODO:move player
	}
}

void Bomberman::drawGridCell(char x, char y){
	_LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, BackgroundColor);

	if(Grid[x][y] == Wall)
		_LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, WallColor);
	else if(Grid[x][y] == Rock)
		_LCD->fillRect(OffsetX + x * GridBlockSize, OffsetY + y * GridBlockSize, GridBlockSize, GridBlockSize, RockColor);
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
