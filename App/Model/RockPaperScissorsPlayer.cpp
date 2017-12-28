/* 
* RockPaperScissorsPlayer.cpp
*
* Created: 27-12-2017 19:20:57
* Author: Gerhard
*/

#include "RockPaperScissorsPlayer.h"

// default constructor
RockPaperScissorsPlayer::RockPaperScissorsPlayer(char ID, uint16_t color, RockPaperScissors *game) : Player()
{
	this->ID = ID;
	this->Color = color;
	this->_game = game;
	this->Updated = 1;
} //RockPaperScissorsPlayer

void RockPaperScissorsPlayer::Draw(MI0283QT9 *LCD){
	if(Updated == 0)
		return;
	
	unsigned char x = ID == 1 ? 25 : 175;
	unsigned char y = 50;

	_game->LCD->drawRect(x, y, 120, 120, Color);
	_game->LCD->fillRect(x+20, y+20, 80, 80, _game->BackgroundColor);
	switch(Direction){
		case Up:
			_game->LCD->fillCircle(x+60, y+60, 30, Color);
			break;
		case Left:
			_game->LCD->fillRect(x+30, y+30, 60, 60, Color);
			break;
		case Right:
			_game->LCD->drawLine(x+40, y+40, x+100, y+100, Color);
			_game->LCD->drawLine(x+40, y+80, x+100, y+20, Color);
			break;
	};
	Updated = 0;
}

// default destructor
RockPaperScissorsPlayer::~RockPaperScissorsPlayer()
{
} //~RockPaperScissorsPlayer
