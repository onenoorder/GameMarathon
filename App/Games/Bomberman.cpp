/* 
* Bomberman.cpp
*
* Created: 14-11-2017 14:05:47
* Author: Gerhard
*/

#include "Bomberman.h"


// default constructor
Bomberman::Bomberman()
{
	this->InitScreen();
	_gridBlockSize = 15;
	_offsetX = 16;
	_offsetY = 8;
	_maxX = 15;
	_maxY = 15;
	
	// Colors
	_wall = RGB(24,24,24);
	_background = RGB(31, 145, 39);
	_rock = RGB(85,85,85);

	// Make grid
	_grid = new char*[_maxX];
	for(char x = 0; x < _maxX; x++)
		_grid[x] = new char[_maxY];
} //Bomberman

void Bomberman::Load()
{
	// Border
	_LCD->fillScreen(_wall);
	// Background
	_LCD->fillRect(_offsetX, _offsetY, _gridBlockSize * _maxX, _gridBlockSize * _maxY, _background);	

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

	/*_players[0] = BombermanPlayer(0,0);
	_grid[_players[0].X][_players[0].Y] = 1;
	drawGridCell(_players[0].X,_players[0].Y);*/

	_currentPlayer = new BombermanPlayer(_maxX-1,_maxY-1, RGB(255, 120, 66));
	_grid[_currentPlayer->X][_currentPlayer->Y] = 1;
	drawGridCell(_currentPlayer->X,_currentPlayer->Y);

	//_players[1] = BombermanPlayer(_maxX-1,_maxY-1);
	//_playercount = 2;	

	
}

void Bomberman::Update(){
	_InputController->UpdateInput();
	Serial.print("Gametime: ");
	Serial.print(GameTime);
	if(_InputController->nunchuckanalogX > 200){
		Serial.println("right");
		_currentPlayer->direction = Right;
		if(_currentPlayer->X+1 < _maxX &&_grid[_currentPlayer->X+1][_currentPlayer->Y] == Walkable){
			_grid[_currentPlayer->X][_currentPlayer->Y] = Walkable;
			drawGridCell(_currentPlayer->X,_currentPlayer->Y);

			_currentPlayer->X++;
			_grid[_currentPlayer->X][_currentPlayer->Y] = 1;
		}
		drawGridCell(_currentPlayer->X,_currentPlayer->Y);
	}else if(_InputController->nunchuckanalogY > 200){
		Serial.println("Up");
		_currentPlayer->direction = Up;
		if(_currentPlayer->Y-1 >= 0 && _grid[_currentPlayer->X][_currentPlayer->Y-1] == Walkable){
			_grid[_currentPlayer->X][_currentPlayer->Y] = Walkable;
			drawGridCell(_currentPlayer->X,_currentPlayer->Y);

			_currentPlayer->Y--;
			_grid[_currentPlayer->X][_currentPlayer->Y] = 1;
		}
		drawGridCell(_currentPlayer->X,_currentPlayer->Y);
	}
	else if(_InputController->nunchuckanalogX < 50){
	Serial.println("Left");
		_currentPlayer->direction = Left;
		 if(_currentPlayer->X-1 >= 0 &&_grid[_currentPlayer->X-1][_currentPlayer->Y] == Walkable){
			_grid[_currentPlayer->X][_currentPlayer->Y] = Walkable;
			drawGridCell(_currentPlayer->X,_currentPlayer->Y);

			_currentPlayer->X--;
			_grid[_currentPlayer->X][_currentPlayer->Y] = 1;
		 }
		 drawGridCell(_currentPlayer->X,_currentPlayer->Y);
	}
	else if(_InputController->nunchuckanalogY < 50){
		Serial.println("Down");
		_currentPlayer->direction = Down;
		if(_currentPlayer->Y+1 < _maxY &&_grid[_currentPlayer->X][_currentPlayer->Y+1] == Walkable){
			_grid[_currentPlayer->X][_currentPlayer->Y] = Walkable;
			drawGridCell(_currentPlayer->X,_currentPlayer->Y);

			_currentPlayer->Y++;
			_grid[_currentPlayer->X][_currentPlayer->Y] = 1;
			
		}

		drawGridCell(_currentPlayer->X,_currentPlayer->Y);
	}	
}

void Bomberman::drawGridCell(char x, char y){
	_LCD->fillRect(_offsetX + x * _gridBlockSize, _offsetY + y * _gridBlockSize, _gridBlockSize, _gridBlockSize, _background);

	if(_grid[x][y] == Wall)
		_LCD->fillRect(_offsetX + x * _gridBlockSize, _offsetY + y * _gridBlockSize, _gridBlockSize, _gridBlockSize, _wall);
	else if(_grid[x][y] >= Rock)
		_LCD->fillRect(_offsetX + x * _gridBlockSize, _offsetY + y * _gridBlockSize, _gridBlockSize, _gridBlockSize, _rock);
	else if(_grid[x][y] == Walkable)
		_LCD->fillRect(_offsetX + x * _gridBlockSize, _offsetY + y * _gridBlockSize, _gridBlockSize, _gridBlockSize, _background);
	else if(_grid[x][y] == Player2 || _grid[x][y] == Player1){		

		if(_currentPlayer->direction == Up){
			_LCD->fillEllipse(_offsetX + x * _gridBlockSize + (_gridBlockSize/2), _offsetY + y * _gridBlockSize + (_gridBlockSize/2), _gridBlockSize/2, _gridBlockSize/4, _currentPlayer->color);
			_LCD->fillRect(_offsetX + x * _gridBlockSize + (_gridBlockSize/2)+3 , _offsetY + y * _gridBlockSize + (_gridBlockSize/2)-7,3,_gridBlockSize/3, RGB(55,55,55));
		}
		else if(_currentPlayer->direction == Right){
			_LCD->fillEllipse(_offsetX + x * _gridBlockSize + (_gridBlockSize/2), _offsetY + y * _gridBlockSize + (_gridBlockSize/2), _gridBlockSize/4, _gridBlockSize/2, _currentPlayer->color);
			_LCD->fillRect(_offsetX + x * _gridBlockSize + (_gridBlockSize/2)+2 , _offsetY + y * _gridBlockSize + (_gridBlockSize/2)-6,_gridBlockSize/3,3, RGB(55,55,55));			
		}
		else if(_currentPlayer->direction == Down){
			_LCD->fillEllipse(_offsetX + x * _gridBlockSize + (_gridBlockSize/2), _offsetY + y * _gridBlockSize + (_gridBlockSize/2), _gridBlockSize/2, _gridBlockSize/4, _currentPlayer->color);
			_LCD->fillRect(_offsetX + x * _gridBlockSize + (_gridBlockSize/2)-6 , _offsetY + y * _gridBlockSize + (_gridBlockSize/2)+2,3,_gridBlockSize/3, RGB(55,55,55));
		}
		else if(_currentPlayer->direction == Left){
			_LCD->fillEllipse(_offsetX + x * _gridBlockSize + (_gridBlockSize/2), _offsetY + y * _gridBlockSize + (_gridBlockSize/2), _gridBlockSize/4, _gridBlockSize/2, _currentPlayer->color);
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
