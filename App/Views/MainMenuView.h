/* 
* MainMenuView.h
*
* Created: 30-11-2017 11:25:19
* Author: Mikena
*/


#ifndef __MAINMENUVIEW_H__
#define __MAINMENUVIEW_H__
#include "View.h"
#include "SelectGameView.h"
class SelectGameView;
class MainMenuView : public View
{
//variables
public:
protected:
private:
	unsigned char _buttonIndex;
	unsigned char _arrowMoved;
	unsigned char _pageSelected;
	enum MainMenuPage{
		SelectGame,
		HighScore
	};

//functions
public:
	virtual void Load();
	virtual void Update();
	MainMenuView(MI0283QT9 *LCD, InputController *inputController);
	~MainMenuView();
protected:
private:
	MainMenuView( const MainMenuView &c );
	MainMenuView& operator=( const MainMenuView &c );

}; //MainMenuView

#endif //__MAINMENUVIEW_H__
