/* 
* BombermanBomb.cpp
*
* Created: 20-11-2017 15:54:39
* Author: Mikena
*/
#include "BombermanBomb.h"

 BombermanBomb::BombermanBomb(char X, char Y,int TimePlaced, BombermanPlayer * Player , int index,Bomberman * game)
{
	this->X = X;
	this->Y = Y;
	this->TimePlaced = TimePlaced;
	this->BombIndex = index;
	this->Player = Player;
	this->Exploding = 0;
	
	this->Ticks = 0;
	this->_game = game;
}

void BombermanBomb::Tick(MI0283QT9 * LCD){
	if(Ticks == 0){
		LCD->fillEllipse(_game->OffsetX + this->X * _game->GridBlockSize + (_game->GridBlockSize/2), _game->OffsetY + this->Y * _game->GridBlockSize + (_game->GridBlockSize/2), _game->GridBlockSize/2, _game->GridBlockSize/2, RGB(89,26,3));
	}else if (Ticks ==1){
		LCD->fillEllipse(_game->OffsetX + this->X * _game->GridBlockSize + (_game->GridBlockSize/2), _game->OffsetY + this->Y * _game->GridBlockSize + (_game->GridBlockSize/2), _game->GridBlockSize/2, _game->GridBlockSize/2, RGB(186,57,11));	
	}else if (Ticks ==2){
		LCD->fillEllipse(_game->OffsetX + this->X * _game->GridBlockSize + (_game->GridBlockSize/2), _game->OffsetY + this->Y * _game->GridBlockSize + (_game->GridBlockSize/2), _game->GridBlockSize/2, _game->GridBlockSize/2, RGB(255,77,18));	
	}
	Ticks++;
}

void BombermanBomb::Explode(MI0283QT9 * LCD){
	this->Exploding = 1;
	char directions = 0x00;

	LCD->fillRect(_game->OffsetX + this->X * _game->GridBlockSize, _game->OffsetY + (this->Y) * _game->GridBlockSize, _game->GridBlockSize, _game->GridBlockSize, RGB(255,0,0));
					
	for (int blast = 0; blast < this->Player->Blastpower; blast++)
	{
		if( !(directions & 0x01) && this->Y+blast+1 < _game->MaxY && _game->Grid[this->X][this->Y+blast+1]  != _game->Wall ){
			if(_game->Grid[this->X][this->Y+blast+1]  == _game->Rock ){
				directions |= 0x01;
			}
			_game->Grid[this->X][this->Y+blast+1] = _game->Explotion;
			LCD->fillRect(_game->OffsetX + this->X * _game->GridBlockSize, _game->OffsetY + (this->Y+blast+1) * _game->GridBlockSize, _game->GridBlockSize, _game->GridBlockSize, RGB(255,0,0));		
		}else{
			directions |= 0x01;
		}

		if(!(directions & 0x02) && this->Y-blast-1 >= 0 && _game->Grid[this->X][this->Y-blast-1]  != _game->Wall ){
			if(_game->Grid[this->X][this->Y-blast-1]  == _game->Rock ){
				directions |= 0x02;
			}
			_game->Grid[this->X][this->Y-blast-1] = _game->Explotion;
			LCD->fillRect(_game->OffsetX + this->X * _game->GridBlockSize, _game->OffsetY + (this->Y-blast-1) * _game->GridBlockSize, _game->GridBlockSize, _game->GridBlockSize, RGB(255,0,0));		
		}else{
			directions |= 0x02;
		}

		if(!(directions & 0x04) && this->X+blast+1 < _game->MaxX && _game->Grid[this->X+blast+1][this->Y] != _game->Wall ){
			if(_game->Grid[this->X+blast+1][this->Y]  == _game->Rock ){
				directions |= 0x04;
			}
			_game->Grid[this->X+blast+1][this->Y] = _game->Explotion;
				LCD->fillRect(_game->OffsetX + (this->X+blast+1) * _game->GridBlockSize, _game->OffsetY + (this->Y) * _game->GridBlockSize, _game->GridBlockSize, _game->GridBlockSize, RGB(255,0,0));

		}else{
			directions |= 0x04;
		}

		if(!(directions & 0x08) && this->X-blast-1 >= 0 && _game->Grid[this->X-blast-1][this->Y] != _game->Wall ){
			if(_game->Grid[this->X-blast-1][this->Y]  == _game->Rock ){
				directions |= 0x08;
			}
			_game->Grid[this->X-blast-1][this->Y] = _game->Explotion;
			LCD->fillRect(_game->OffsetX + (this->X-blast-1) * _game->GridBlockSize, _game->OffsetY + (this->Y) * _game->GridBlockSize, _game->GridBlockSize, _game->GridBlockSize, RGB(255,0,0));

		}else{
			directions |= 0x08;
		}
	}
}

// default destructor
BombermanBomb::~BombermanBomb()
{
} //~BombermanBomb
