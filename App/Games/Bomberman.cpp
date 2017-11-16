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
	_maxX = 19;
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
				_grid[x][y] = 0;
			// Player 3 location
			else if(x == _maxX - 1 && y < 3 || y == 0 && x > _maxX-4)
				_grid[x][y] = 0;
			// Player 4 location
			else if(y == _maxY - 1 && x < 3 || x == 0 && y > _maxY-4)
				_grid[x][y] = 0;
			// Player 2 location
			else if(y == _maxY - 1 && x > _maxX - 4 || x == _maxX-1 && y > _maxY-4)
				_grid[x][y] = 0;
			// Wall
			else if(x % 2 == 1 && y % 2 == 1)
				_grid[x][y] = 64;
			// Rock
			else
				_grid[x][y] = 32;

			// Wall
			if(_grid[x][y] > 32)
				_LCD->fillRect(_offsetX + x * _gridBlockSize, _offsetY + y * _gridBlockSize, _gridBlockSize, _gridBlockSize, _wall);
			// Rock
			else if(_grid[x][y] > 16)
				_LCD->fillRect(_offsetX + x * _gridBlockSize, _offsetY + y * _gridBlockSize, _gridBlockSize, _gridBlockSize, _rock);
		}
	}
}

// default destructor
Bomberman::~Bomberman()
{
	delete[] _grid;
} //~Bomberman
