/* 
* BombermanBomb.cpp
*
* Created: 20-11-2017 15:54:39
* Author: Mikena & Gerhard
*/
#include "BombermanBomb.h"

// contructor
 BombermanBomb::BombermanBomb(char X, char Y,int TimePlaced, BombermanPlayer * Player ,Bomberman * game)
{
	this->X = X;
	this->Y = Y;
	this->TimePlaced = TimePlaced;

	this->Player = Player;
	this->Exploding = 0;
	
	this->Ticks = 0;
	this->_game = game;
}


//laat bom tikken
void BombermanBomb::Tick(MI0283QT9 * LCD){
	LCD->fillEllipse(_game->OffsetX + this->X * _game->GridBlockSize + (_game->GridBlockSize/2), _game->OffsetY + this->Y * _game->GridBlockSize + (_game->GridBlockSize/2), _game->GridBlockSize/2, _game->GridBlockSize/2, RGB(0,0,0));
	LCD->fillEllipse(_game->OffsetX + this->X * _game->GridBlockSize + (_game->GridBlockSize/2), _game->OffsetY + this->Y * _game->GridBlockSize + (_game->GridBlockSize/2), _game->GridBlockSize/4, _game->GridBlockSize/4, _game->RockColor);
	LCD->fillEllipse(_game->OffsetX + this->X * _game->GridBlockSize + (_game->GridBlockSize/2), _game->OffsetY + this->Y * _game->GridBlockSize + (_game->GridBlockSize/2), _game->GridBlockSize/6, _game->GridBlockSize/6, _game->RockGlowColor);
	
	if(Ticks == 0){
		LCD->drawLine(_game->OffsetX + this->X * _game->GridBlockSize + (_game->GridBlockSize/2), _game->OffsetY + this->Y * _game->GridBlockSize + (_game->GridBlockSize/2), _game->OffsetX + this->X * _game->GridBlockSize + _game->GridBlockSize*0.8, _game->OffsetY + this->Y * _game->GridBlockSize + _game->GridBlockSize*0.2, RGB(240, 170, 1));
		LCD->fillEllipse(_game->OffsetX + this->X * _game->GridBlockSize + _game->GridBlockSize*0.8, _game->OffsetY + this->Y * _game->GridBlockSize + _game->GridBlockSize*0.2, _game->GridBlockSize/8, _game->GridBlockSize/8, _game->ExplotionTextColor);
	} else if (Ticks == 1){
		LCD->drawLine(_game->OffsetX + this->X * _game->GridBlockSize + (_game->GridBlockSize/2), _game->OffsetY + this->Y * _game->GridBlockSize + (_game->GridBlockSize/2), _game->OffsetX + this->X * _game->GridBlockSize + _game->GridBlockSize*0.7, _game->OffsetY + this->Y * _game->GridBlockSize + _game->GridBlockSize*0.3, RGB(240, 170, 1));
		LCD->fillEllipse(_game->OffsetX + this->X * _game->GridBlockSize + _game->GridBlockSize*0.7, _game->OffsetY + this->Y * _game->GridBlockSize + _game->GridBlockSize*0.3, _game->GridBlockSize/8, _game->GridBlockSize/8, _game->ExplotionTextColor);
	} else if (Ticks == 2){
		LCD->drawLine(_game->OffsetX + this->X * _game->GridBlockSize + (_game->GridBlockSize/2), _game->OffsetY + this->Y * _game->GridBlockSize + (_game->GridBlockSize/2), _game->OffsetX + this->X * _game->GridBlockSize + _game->GridBlockSize*0.6, _game->OffsetY + this->Y * _game->GridBlockSize + _game->GridBlockSize*0.4, RGB(240, 170, 1));
		LCD->fillEllipse(_game->OffsetX + this->X * _game->GridBlockSize + _game->GridBlockSize*0.6, _game->OffsetY + this->Y * _game->GridBlockSize + _game->GridBlockSize*0.4, _game->GridBlockSize/8, _game->GridBlockSize/8, _game->ExplotionTextColor);
	}
	Ticks++;
}

//doet bom exploderen
void BombermanBomb::Explode(MI0283QT9 * LCD, unsigned char explotionTime){
	this->Exploding = 1;
	char directions = 0x00;

	LCD->fillRect(_game->OffsetX + this->X * _game->GridBlockSize, _game->OffsetY + (this->Y) * _game->GridBlockSize, _game->GridBlockSize, _game->GridBlockSize, _game->ExplotionTextColor);
	_game->Grid[this->X][this->Y] = _game->Explotion;	

	for (int blast = 0; blast < this->Player->Blastpower; blast++)
	{
		unsigned char explotion = 0;

		if(blast == 0)
			explotion = _game->Explotion_1;
		else if(blast == 1)
			explotion = _game->Explotion_2;
		else if(blast == 2)
			explotion = _game->Explotion_3;
		else
			explotion = _game->Explotion;

		explotion += explotionTime;

		if( !(directions & 0x01) && this->Y+blast+1 < _game->MaxY && _game->Grid[this->X][this->Y+blast+1]  != _game->Wall){
			if(_game->Grid[this->X][this->Y+blast+1]  == _game->Rock || (explotionTime > 0 && _game->Grid[this->X][this->Y+blast+1]  == _game->Walkable)){
				directions |= 0x01;
			}

			if(explotionTime == 0 || !(directions & 0x01)){
				_game->Grid[this->X][this->Y+blast+1] = explotion;
				_game->DrawGridCell(this->X, this->Y+blast+1);
			}
		}else{
			directions |= 0x01;
		}

		if(!(directions & 0x02) && this->Y-blast-1 >= 0 && _game->Grid[this->X][this->Y-blast-1]  != _game->Wall){
			if(_game->Grid[this->X][this->Y-blast-1]  == _game->Rock || (explotionTime > 0 && _game->Grid[this->X][this->Y-blast-1]  == _game->Walkable)){
				directions |= 0x02;
			}

			if(explotionTime == 0 || !(directions & 0x02)){
				_game->Grid[this->X][this->Y-blast-1] = explotion;
				_game->DrawGridCell(this->X, this->Y-blast-1);
			}
		}else{
			directions |= 0x02;
		}

		if(!(directions & 0x04) && this->X+blast+1 < _game->MaxX && _game->Grid[this->X+blast+1][this->Y] != _game->Wall){
			if(_game->Grid[this->X+blast+1][this->Y]  == _game->Rock || (explotionTime > 0 && _game->Grid[this->X+blast+1][this->Y]  == _game->Walkable)){
				directions |= 0x04;
			}

			if(explotionTime == 0 || !(directions & 0x04)){
				_game->Grid[this->X+blast+1][this->Y] = explotion;
				_game->DrawGridCell(this->X+blast+1, this->Y);
			}
		}else{
			directions |= 0x04;
		}

		if(!(directions & 0x08) && this->X-blast-1 >= 0 && _game->Grid[this->X-blast-1][this->Y] != _game->Wall){
			if(_game->Grid[this->X-blast-1][this->Y]  == _game->Rock || (explotionTime > 0 && _game->Grid[this->X-blast-1][this->Y]  == _game->Walkable)){
				directions |= 0x08;
			}

			if(explotionTime == 0 || !(directions & 0x08)){
				_game->Grid[this->X-blast-1][this->Y] = explotion;
				_game->DrawGridCell(this->X-blast-1, this->Y);
			}
		}else{
			directions |= 0x08;
		}
	}
}

// default destructor
BombermanBomb::~BombermanBomb()
{
} //~BombermanBomb
