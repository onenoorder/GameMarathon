/* 
* MainMenuView.cpp
*
* Created: 30-11-2017 11:25:18
* Author: Mikena
*/

#include "MainMenuView.h"

// x 360 y 240
// default constructor
MainMenuView::MainMenuView(MI0283QT9 *LCD, InputController *inputController, Communication * communication) :View(LCD, inputController,  communication)
{
	_buttonIndex = 0;
	_arrowMoved = 1;
	_pageSelected = 1;
} //MainMenuView

//laad mainmenu-scherm, als master --> schrijf master etc.
void MainMenuView::Load(){
	LCD->fillScreen(RGB(0,0,0));
	LCD->drawText(95,5, "GAME", RGB(255,0,0),RGB(0,0,0),4);
	LCD->drawText(32,40, "MARATHON", RGB(255,0,0),RGB(0,0,0),4);
	LCD->fillRect (32,80,320-64,6, RGB(255,0,0));
	
	LCD->drawText(80,120, "Select Game", RGB(255,0,0),RGB(0,0,0),2);
	LCD->drawText(80,160, "High score", RGB(255,0,0),RGB(0,0,0),2);

	if(GLBL_Role == RL_SLAVE){	
		LCD->drawText(10,230, "Slave", RGB(255,255,255),RGB(0,0,0),1);
	}else{
		LCD->drawText(10,230, "Master", RGB(255,255,255),RGB(0,0,0),1);

	}
	Loaded = 1;
}

// mainmenuscherm updaten op basis van input met controller.
void MainMenuView::Update(){
	View::Update();
	Input->UpdateInput();

	if(Input->NunchuckAnalogY > 200 && _buttonIndex > 0){
		_buttonIndex--;
		_arrowMoved = 1;
	}
	else if(Input->NunchuckAnalogY < 50 && _buttonIndex < 1){
		_buttonIndex++;
		_arrowMoved = 1;
	}

	if(Input->LCDTouchX > 600 && Input->LCDTouchX < 900){
		if(Input->LCDTouchY > 220 && Input->LCDTouchY < 300){
			_buttonIndex = SelectGame;
			_pageSelected = 0;
			_arrowMoved = 1;
		} else if(Input->LCDTouchY > 300){
			_buttonIndex = HighScore;
			_pageSelected = 0;
			_arrowMoved = 1;
		}
	}

	if(Input->NunchuckZButton)
		_pageSelected = 0;

	if(_arrowMoved){
		LCD->fillTriangle(50,155 , 70, 165, 50, 175, RGB(0,0,0));
		LCD->fillTriangle(50,115 , 70, 125, 50, 135, RGB(0,0,0));
		switch(_buttonIndex){
			case SelectGame:
				LCD->fillTriangle(50, 115 , 70, 125, 50, 135, RGB(0,255,0));
				break;
			case HighScore:
				LCD->fillTriangle(50, 155 , 70, 165, 50, 175, RGB(0,255,0));
				break;
			
		}
		_arrowMoved = 0;
	}

	if(_pageSelected == 0){
		_pageSelected = 1;
		switch(_buttonIndex){
			case SelectGame:
				new SelectGameView(LCD,Input, CommunicationHandler);
				break;
			case HighScore:
				new HighScoreView(LCD,Input, CommunicationHandler);
				break;
		}
	}
}

// default destructor
MainMenuView::~MainMenuView()
{
} //~MainMenuView
