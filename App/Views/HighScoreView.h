/* 
* HighScoreView.h
*
* Created: 19-12-2017 11:54:24
* Author: Gerhard
*/

#ifndef __HIGHSCOREVIEW_H__
#define __HIGHSCOREVIEW_H__

#include "View.h"
#include "MainMenuView.h"

class HighScoreView : public View
{
//variables
public:
	unsigned char _buttonIndex;
	unsigned char _arrowMoved;
	unsigned char _pageSelected;
	enum HighScorePage{
		MainMenu
	};
protected:
private:

//functions
public:
	HighScoreView(MI0283QT9 *LCD, InputController *inputController, Communication *communication);
	virtual void Load();
	virtual void Update();
	~HighScoreView();
protected:
private:

}; //HighScoreView

#endif //__HIGHSCOREVIEW_H__
