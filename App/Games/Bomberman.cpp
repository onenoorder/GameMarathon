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
	_gridBlockSize = 15;
	_offsetX = 16;
	_offsetY = 8;
	_maxX = 19;
	_maxY = 15;
	BombsActiveCount = 0;
	BombStartIndex = 0;
	// Colors
	_wallColor = RGB(24,24,24);
	_backgroundColor = RGB(31, 145, 39);
	_rockColor = RGB(85,85,85);

	// Make grid
	_grid = new char*[_maxX];
	for(char x = 0; x < _maxX; x++)
		_grid[x] = new char[_maxY];
} //Bomberman

void Bomberman::Load()
{
	// Border
	_LCD->fillScreen(_wallColor);
	// Background
	_LCD->fillRect(_offsetX, _offsetY, _gridBlockSize * _maxX, _gridBlockSize * _maxY, _backgroundColor);

	for(char x = 0; x < _maxX; x++){
		for(char y = 0; y < _maxY; y++){
			// Player 1 location
			if(x == 0 && y < 3 || y == 0 && x < 3)
				_grid[x][y] = Walkable;
			// Player 3 location
			else if(x == _maxX - 1 && y < 3 || y == 0 && x > _maxX-4)
				_grid[x][y] = Walkable;
			// Player 4 location
			else if(y == _maxY - 1 && x < 3 || x == 0 && y > _maxY-4)
				_grid[x][y] = Walkable;
			// Player 2 location
			else if(y == _maxY - 1 && x > _maxX - 4 || x == _maxX-1 && y > _maxY-4)
				_grid[x][y] = Walkable;
			// Wall
			else if(x % 2 == 1 && y % 2 == 1)
				_grid[x][y] = Wall;
			// Rock
			else
				_grid[x][y] = Rock;
				
			drawGridCell(x,y);
		}
	}

	_players[0] = new BombermanPlayer(0, 0, RGB(255, 120, 66));
	_players[1] = new BombermanPlayer(_maxX-1, _maxY-1, RGB(255, 120, 66));
	
	_grid[_players[0]->X][_players[0]->Y] = 1;
	_grid[_players[1]->X][_players[1]->Y] = 1;

	drawGridCell(_players[0]->X, _players[0]->Y);
	drawGridCell(_players[1]->X, _players[1]->Y);

	_currentPlayer = _players[PlayerID];
}

void Bomberman::Update(){
	Game::Update();
	_InputController->UpdateInput();

	if(_InputController->NunchuckAnalogX > 200){
		Serial.println("right");
		_currentPlayer->Direction = Right;
		if(_currentPlayer->X+1 < _maxX &&_grid[_currentPlayer->X+1][_currentPlayer->Y] == Walkable){
			if(_grid[_currentPlayer->X][_currentPlayer->Y] != Bomb)
				_grid[_currentPlayer->X][_currentPlayer->Y] = Walkable;
			drawGridCell(_currentPlayer->X,_currentPlayer->Y);

			_currentPlayer->X++;
			_grid[_currentPlayer->X][_currentPlayer->Y] = 1;
		}
		drawGridCell(_currentPlayer->X,_currentPlayer->Y);
	}else if(_InputController->NunchuckAnalogY > 200){
		Serial.println("Up");
		_currentPlayer->Direction = Up;
		if(_currentPlayer->Y-1 >= 0 && _grid[_currentPlayer->X][_currentPlayer->Y-1] == Walkable){
			if(_grid[_currentPlayer->X][_currentPlayer->Y] != Bomb)
				_grid[_currentPlayer->X][_currentPlayer->Y] = Walkable;
			drawGridCell(_currentPlayer->X,_currentPlayer->Y);

			_currentPlayer->Y--;
			_grid[_currentPlayer->X][_currentPlayer->Y] = 1;
		}
		drawGridCell(_currentPlayer->X,_currentPlayer->Y);
	}
	else if(_InputController->NunchuckAnalogX < 50){
	Serial.println("Left");
		_currentPlayer->Direction = Left;
		 if(_currentPlayer->X-1 >= 0 &&_grid[_currentPlayer->X-1][_currentPlayer->Y] == Walkable){
			if(_grid[_currentPlayer->X][_currentPlayer->Y] != Bomb)
				_grid[_currentPlayer->X][_currentPlayer->Y] = Walkable;
			drawGridCell(_currentPlayer->X,_currentPlayer->Y);

			_currentPlayer->X--;
			_grid[_currentPlayer->X][_currentPlayer->Y] = 1;
		 }
		 drawGridCell(_currentPlayer->X,_currentPlayer->Y);
	}
	else if(_InputController->NunchuckAnalogY < 50){
		Serial.println("Down");
		_currentPlayer->Direction = Down;
		if(_currentPlayer->Y+1 < _maxY &&_grid[_currentPlayer->X][_currentPlayer->Y+1] == Walkable){
			if(_grid[_currentPlayer->X][_currentPlayer->Y] != Bomb)
				_grid[_currentPlayer->X][_currentPlayer->Y] = Walkable;

			drawGridCell(_currentPlayer->X,_currentPlayer->Y);

			_currentPlayer->Y++;
			_grid[_currentPlayer->X][_currentPlayer->Y] = 1;			
		}
		drawGridCell(_currentPlayer->X,_currentPlayer->Y);
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

	if(_InputController->NunchuckZButton){
		_bombs[BombsActiveCount] = new  BombermanBomb(_currentPlayer->X,_currentPlayer->Y,GameTime, _currentPlayer, BombsActiveCount);
		_grid[_currentPlayer->X][_currentPlayer->Y] = Bomb;
		drawGridCell(_currentPlayer->X,_currentPlayer->Y);
		BombsActiveCount ++;
		if(BombsActiveCount == 16){
			BombsActiveCount = 0;
		}
	}
	for(char i = BombStartIndex; i < BombsActiveCount; i++){
		BombermanBomb * bomb = _bombs[i];
		if(bomb->TimePlaced+3 <= GameTime ){
			//explode
			_grid[bomb->X][bomb->Y] = Walkable;
			_grid[bomb->X][bomb->Y+1] = Walkable;
			_grid[bomb->X][bomb->Y-1] = Walkable;
			_grid[bomb->X+1][bomb->Y] = Walkable;
			_grid[bomb->X-1][bomb->Y] = Walkable;

			drawGridCell(bomb->X,bomb->Y);
			drawGridCell(bomb->X,bomb->Y+1);
			drawGridCell(bomb->X,bomb->Y-1);
			drawGridCell(bomb->X+1,bomb->Y);
			drawGridCell(bomb->X-1,bomb->Y);
			BombStartIndex++;

			if(BombStartIndex == 16){
				BombStartIndex = 0;
			}
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
	_LCD->fillRect(_offsetX + x * _gridBlockSize, _offsetY + y * _gridBlockSize, _gridBlockSize, _gridBlockSize, _backgroundColor);

	if(_grid[x][y] == Wall)
		_LCD->fillRect(_offsetX + x * _gridBlockSize, _offsetY + y * _gridBlockSize, _gridBlockSize, _gridBlockSize, _wallColor);
	else if(_grid[x][y] == Rock)
		_LCD->fillRect(_offsetX + x * _gridBlockSize, _offsetY + y * _gridBlockSize, _gridBlockSize, _gridBlockSize, _rockColor);
	else if(_grid[x][y] == Walkable)
		_LCD->fillRect(_offsetX + x * _gridBlockSize, _offsetY + y * _gridBlockSize, _gridBlockSize, _gridBlockSize, _backgroundColor);
	else if(_grid[x][y] == Bomb){
			_LCD->fillEllipse(_offsetX + x * _gridBlockSize + (_gridBlockSize/2), _offsetY + y * _gridBlockSize + (_gridBlockSize/2), _gridBlockSize/2, _gridBlockSize/2, RGB(0,0,0));
			}			
	else if(_grid[x][y] == BOMBERMAN_PLAYER2 || _grid[x][y] == BOMBERMAN_PLAYER1){
		if(_currentPlayer->Direction == Up){
			_LCD->fillEllipse(_offsetX + x * _gridBlockSize + (_gridBlockSize/2), _offsetY + y * _gridBlockSize + (_gridBlockSize/2), _gridBlockSize/2, _gridBlockSize/4, _currentPlayer->Color);
			_LCD->fillRect(_offsetX + x * _gridBlockSize + (_gridBlockSize/2)+3 , _offsetY + y * _gridBlockSize + (_gridBlockSize/2)-7,3,_gridBlockSize/3, RGB(55,55,55));
		}
		else if(_currentPlayer->Direction == Right){
			_LCD->fillEllipse(_offsetX + x * _gridBlockSize + (_gridBlockSize/2), _offsetY + y * _gridBlockSize + (_gridBlockSize/2), _gridBlockSize/4, _gridBlockSize/2, _currentPlayer->Color);
			_LCD->fillRect(_offsetX + x * _gridBlockSize + (_gridBlockSize/2)+2 , _offsetY + y * _gridBlockSize + (_gridBlockSize/2)-6,_gridBlockSize/3,3, RGB(55,55,55));
		}
		else if(_currentPlayer->Direction == Down){
			_LCD->fillEllipse(_offsetX + x * _gridBlockSize + (_gridBlockSize/2), _offsetY + y * _gridBlockSize + (_gridBlockSize/2), _gridBlockSize/2, _gridBlockSize/4, _currentPlayer->Color);
			_LCD->fillRect(_offsetX + x * _gridBlockSize + (_gridBlockSize/2)-6 , _offsetY + y * _gridBlockSize + (_gridBlockSize/2)+2,3,_gridBlockSize/3, RGB(55,55,55));
		}
		else if(_currentPlayer->Direction == Left){
			_LCD->fillEllipse(_offsetX + x * _gridBlockSize + (_gridBlockSize/2), _offsetY + y * _gridBlockSize + (_gridBlockSize/2), _gridBlockSize/4, _gridBlockSize/2, _currentPlayer->Color);
			_LCD->fillRect(_offsetX + x * _gridBlockSize + (_gridBlockSize/2)-7 , _offsetY + y * _gridBlockSize + (_gridBlockSize/2)+3,_gridBlockSize/3,3, RGB(55,55,55));
		}

		_LCD->fillCircle(_offsetX + x * _gridBlockSize + (_gridBlockSize/2), _offsetY + y * _gridBlockSize + (_gridBlockSize/2), _gridBlockSize/6, RGB(0, 0, 0));
			

	}
}


// default destructor
Bomberman::~Bomberman()
{
	delete[] _grid;
} //~Bomberman
