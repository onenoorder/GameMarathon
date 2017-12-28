/* 
* SelectGameView.h
*
* Created: 30-11-2017 13:42:15
* Author: Mikena & Gerhard
*/

#ifndef __SELECTGAMEVIEW_H__
#define __SELECTGAMEVIEW_H__
#include "View.h"
#include "MainMenuView.h"
#include "../Games/Bomberman.h"
#include "../Games/Snake.h"
#include "../Games//RockPaperScissors.h"

class MainMenuView;

class SelectGameView: public View
{
//variables
public:
protected:
private:
	unsigned char _buttonIndex;
	unsigned char _arrowMoved;
	unsigned int _timeMoved;
	unsigned char _pageSelected;
	enum SelectGamePage{
		BombermanGame = 0,
		SnakeGame = 1,
		RockPaperScissorsGame = 2,
		Marathon = 3,
		Back = 4
	};
//functions
public:
	SelectGameView(MI0283QT9 *LCD, InputController *inputController, Communication * communication);
	virtual void Load();
	virtual void Update();
	void drawMenu();
	void drawBombermanFrame();
	~SelectGameView();
protected:
private:


}; //SelectGameView

#endif //__SELECTGAMEVIEW_H__
