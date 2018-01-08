/* 
* HighScoreView.cpp
*
* Created: 19-12-2017 11:54:24
* Author: Gerhard
*/

#include "HighScoreView.h"

// default constructor
HighScoreView::HighScoreView(MI0283QT9 *LCD, InputController *inputController, Communication *communication) :View(LCD, inputController,  communication)
{
	_buttonIndex = MainMenu;
	_arrowMoved = 1;
	_pageSelected = 1;
} //HighScoreView

void HighScoreView::Load(){
	LCD->fillScreen(RGB(0,0,0));
	LCD->drawText(95, 5, "HIGH", RGB(255,0,0), RGB(0,0,0), 4);
	LCD->drawText(75, 40, "SCORE", RGB(255,0,0), RGB(0,0,0), 4);
	LCD->fillRect(32, 80, 320-64, 6, RGB(255,0,0));

	LCD->drawText(80,100, "Player", RGB(255,255,0),RGB(0,0,0),1);
	LCD->drawText(140,100, "Score", RGB(255,255,0),RGB(0,0,0),1);

	LCD->drawText(80,120, "1 :", RGB(255,255,0),RGB(0,0,0),1);
	LCD->drawInteger(140,120, Players[0]->Score, DEC, RGB(255,255,0),RGB(0,0,0),1);
	
	LCD->drawText(80,140, "2 :", RGB(255,255,0),RGB(0,0,0),1);
	LCD->drawInteger(140,140, Players[1]->Score, DEC, RGB(255,255,0),RGB(0,0,0),1);

	LCD->drawText(80,200, "To Main Menu", RGB(255,0,0),RGB(0,0,0),2);
	Loaded = 1;
}

void HighScoreView::Update(){
	View::Update();
	Input->UpdateInput();
	
	if(Input->LCDTouchY > 400){
		_buttonIndex = MainMenu;
		_pageSelected = 0;
	}

	if(Input->NunchuckZButton)
	_pageSelected = 0;

	if(_pageSelected == 0){
		_pageSelected = 1;
		switch(_buttonIndex){
			case MainMenu:
			new MainMenuView(LCD, Input, CommunicationHandler);
			break;
		}
	}

	if(_arrowMoved){//120
		LCD->fillTriangle(50,195 , 70, 202, 50, 215, RGB(0,0,0));
		switch(_buttonIndex){
			case MainMenu:
			LCD->fillTriangle(50,195 , 70, 202, 50, 215, RGB(0,255,0));
			break;
		}
		_arrowMoved = 0;
	}
}

// default destructor
HighScoreView::~HighScoreView()
{
} //~HighScoreView
