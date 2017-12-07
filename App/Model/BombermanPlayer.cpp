/* 
* BombermanPlayer.cpp
*
* Created: 17-11-2017 12:42:19
* Author: Mikena & Gerhard
*/

#include "BombermanPlayer.h"

// default constructor
BombermanPlayer::BombermanPlayer(char X,char Y, uint16_t color, Bomberman * game) : Player()
{
	this->X = X;
	this->Y = Y;
	this->Direction = Up;
	this->Color = color;
	this->ShadowColor = RGB(166, 24, 204);
	this->Blastpower = 5;
	this->Bombs = 0;
	this->MaxBombs = 1;
	this->_game = game;
	this->PlayerUpdated = 0;
	this->BombTime = 0;
	this->Alive = 1;
} //BombermanPlayer

void BombermanPlayer::Move(){
	if(Alive == 0) return;
	if(Direction == Right){
		if(this->X+1 < _game->MaxX &&_game->Grid[this->X+1][this->Y] < _game->Bomb){
			if(_game->Grid[this->X][this->Y] != _game->Bomb)
				_game->Grid[this->X][this->Y] = _game->Walkable;	
			
				this->X++;
				if ( _game->Grid[this->X][this->Y] != _game->Explotion)
					_game->Grid[this->X][this->Y] = 1;
			}
		
	}else if(Direction == Up){
		if(this->Y-1 >= 0 && _game->Grid[this->X][this->Y-1] < _game->Bomb){
			if(_game->Grid[this->X][this->Y] != _game->Bomb)
				_game->Grid[this->X][this->Y] = _game->Walkable;
		
			this->Y--;
			if ( _game->Grid[this->X][this->Y] != _game->Explotion)
				_game->Grid[this->X][this->Y] = 1;
		}

	}
	else if(Direction == Left){
		if(this->X-1 >= 0 &&_game->Grid[this->X-1][this->Y] < _game->Bomb){
			if(_game->Grid[this->X][this->Y] != _game->Bomb)
			_game->Grid[this->X][this->Y] = _game->Walkable;		

			this->X--;
			if ( _game->Grid[this->X][this->Y] != _game->Explotion)
				_game->Grid[this->X][this->Y] = 1;
		}
	
	}
	else if(Direction == Down){
		if(this->Y+1 < _game->MaxY &&_game->Grid[this->X][this->Y+1] < _game->Bomb){
			if(_game->Grid[this->X][this->Y] != _game->Bomb)
			_game->Grid[this->X][this->Y] = _game->Walkable;		
		
			this->Y++;
			if ( _game->Grid[this->X][this->Y] != _game->Explotion)
				_game->Grid[this->X][this->Y] = 1;
		}	
	}
}

void BombermanPlayer::DrawPlayer(MI0283QT9 * LCD){	
	if(Alive == 0) return;
		if(this->Direction == Up){
			LCD->fillEllipse(_game->OffsetX + this->X * _game->GridBlockSize + (_game->GridBlockSize/2), _game->OffsetY + this->Y * _game->GridBlockSize + (_game->GridBlockSize/2)+1, _game->GridBlockSize/2, _game->GridBlockSize/4+1, this->ShadowColor);
			LCD->fillEllipse(_game->OffsetX + this->X * _game->GridBlockSize + (_game->GridBlockSize/2), _game->OffsetY + this->Y * _game->GridBlockSize + (_game->GridBlockSize/2), _game->GridBlockSize/2, _game->GridBlockSize/4, this->Color);
			LCD->fillRect(_game->OffsetX + this->X * _game->GridBlockSize + (_game->GridBlockSize/2)*1.5 , _game->OffsetY + this->Y * _game->GridBlockSize + (_game->GridBlockSize/2)*0.2,_game->GridBlockSize/6,_game->GridBlockSize/2.5, RGB(55,55,55));
		}
		else if(this->Direction == Right){
			LCD->fillEllipse(_game->OffsetX + this->X * _game->GridBlockSize + (_game->GridBlockSize/2)-1, _game->OffsetY + this->Y * _game->GridBlockSize + (_game->GridBlockSize/2), _game->GridBlockSize/4, _game->GridBlockSize/2, this->ShadowColor);
			LCD->fillEllipse(_game->OffsetX + this->X * _game->GridBlockSize + (_game->GridBlockSize/2), _game->OffsetY + this->Y * _game->GridBlockSize + (_game->GridBlockSize/2), _game->GridBlockSize/4, _game->GridBlockSize/2, this->Color);
			LCD->fillRect(_game->OffsetX + this->X * _game->GridBlockSize + (_game->GridBlockSize/2)*1.1 , _game->OffsetY + this->Y * _game->GridBlockSize + (_game->GridBlockSize/2)*0.3,_game->GridBlockSize/2.5,_game->GridBlockSize/6, RGB(55,55,55));
		}
		else if(this->Direction == Down){
			LCD->fillEllipse(_game->OffsetX + this->X * _game->GridBlockSize + (_game->GridBlockSize/2), _game->OffsetY + this->Y * _game->GridBlockSize + (_game->GridBlockSize/2)-1, _game->GridBlockSize/2, _game->GridBlockSize/4+1, this->ShadowColor);
			LCD->fillEllipse(_game->OffsetX + this->X * _game->GridBlockSize + (_game->GridBlockSize/2), _game->OffsetY + this->Y * _game->GridBlockSize + (_game->GridBlockSize/2), _game->GridBlockSize/2, _game->GridBlockSize/4, this->Color);
			LCD->fillRect(_game->OffsetX + this->X * _game->GridBlockSize + (_game->GridBlockSize/2)*0.3 , _game->OffsetY + this->Y * _game->GridBlockSize + (_game->GridBlockSize/2)*1.1,_game->GridBlockSize/6,_game->GridBlockSize/2.5, RGB(55,55,55));
		}
		else if(this->Direction == Left){
			LCD->fillEllipse(_game->OffsetX + this->X * _game->GridBlockSize + (_game->GridBlockSize/2)+1, _game->OffsetY + this->Y * _game->GridBlockSize + (_game->GridBlockSize/2), _game->GridBlockSize/4+1, _game->GridBlockSize/2, this->ShadowColor);
			LCD->fillEllipse(_game->OffsetX + this->X * _game->GridBlockSize + (_game->GridBlockSize/2), _game->OffsetY + this->Y * _game->GridBlockSize + (_game->GridBlockSize/2), _game->GridBlockSize/4, _game->GridBlockSize/2, this->Color);
			LCD->fillRect(_game->OffsetX + this->X * _game->GridBlockSize + (_game->GridBlockSize/2)*0.2 , _game->OffsetY + this->Y * _game->GridBlockSize + (_game->GridBlockSize/2)*1.5,_game->GridBlockSize/2.5,_game->GridBlockSize/6, RGB(55,55,55));
		}

		LCD->fillCircle(_game->OffsetX + this->X * _game->GridBlockSize + (_game->GridBlockSize/2), _game->OffsetY + this->Y * _game->GridBlockSize + (_game->GridBlockSize/2), _game->GridBlockSize/6, RGB(0, 0, 0));
}

// default destructor
BombermanPlayer::~BombermanPlayer()
{
} //~BombermanPlayer
