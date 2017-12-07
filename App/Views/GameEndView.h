/* 
* GameEndView.h
*
* Created: 7-12-2017 10:34:16
* Author: Mikena
*/


#ifndef __GAMEENDVIEW_H__
#define __GAMEENDVIEW_H__
#include "MainMenuView.h"
#include "View.h"
#include "../Model/Player.h"
class MainMenuView;

class GameEndView: public View
{
//variables
public:
	Player * GamePlayer;
	unsigned char _buttonIndex;
	unsigned char _arrowMoved;
	unsigned char _pageSelected;
		enum GameEndPage{
			MainMenu
		};
protected:
private:

//functions
public:
	virtual void Load();
	virtual void Update();
	GameEndView(MI0283QT9 *LCD, InputController *inputController, Communication * communication, Player * player);
protected:


}; //GameEndView

#endif //__GAMEENDVIEW_H__
