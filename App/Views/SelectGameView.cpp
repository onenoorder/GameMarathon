/* 
* SelectGameView.cpp
*
* Created: 30-11-2017 13:42:14
* Author: Mikena
*/


#include "SelectGameView.h"
// x 360 y 240
// default constructor
SelectGameView::SelectGameView(MI0283QT9 *LCD, InputController *inputController):View(LCD, inputController)
{
	_buttonIndex = 0;
	_arrowMoved = 1;
	_pageSelected = 0;
	_timeMoved = GameFastTime;

} //SelectGameView


void SelectGameView::Load(){
	LCD->fillScreen(RGB(0,0,0));
	LCD->fillRect(20,20,130,80,RGB(255,0,0));
	LCD->fillRect(170,20,130,80,RGB(255,0,0));
	LCD->fillRect(20,120,130,80,RGB(255,0,0));
	LCD->fillRect(170,120,130,80,RGB(255,0,0));
	LCD->drawText(80,220, "Back to main", RGB(255,0,0),RGB(0,0,0),2);
	Loaded = 1;
}

void SelectGameView::Update(){
	Input->UpdateInput();

	if(Input->NunchuckAnalogX > 200 && !_arrowMoved && _timeMoved +2 < GameFastTime){
	//right
		if(_buttonIndex == BombermanGame || _buttonIndex  == PongGame){
			_buttonIndex ++;
			_arrowMoved = 1;
			_timeMoved = GameFastTime;
		}
	}else if(Input->NunchuckAnalogY > 200 && !_arrowMoved && _timeMoved +2 < GameFastTime){
	// up
		if(_buttonIndex == PongGame || _buttonIndex  == Marathon || _buttonIndex ==Back ){
			_buttonIndex -=2;
			_arrowMoved = 1;	
			_timeMoved = GameFastTime;		
		}
	}
	else if(Input->NunchuckAnalogX < 50 && !_arrowMoved && _timeMoved +2 < GameFastTime){
	// left
		if(_buttonIndex == SnakeGame || _buttonIndex  == Marathon){
			_buttonIndex --;
			_arrowMoved = 1;
			_timeMoved = GameFastTime;
		}
	}
	else if(Input->NunchuckAnalogY < 50 && !_arrowMoved && _timeMoved +2 < GameFastTime){
	// down
		if( _buttonIndex  == Marathon ){
			_buttonIndex ++;
			_arrowMoved = 1;
			_timeMoved = GameFastTime;
		}else if(_buttonIndex == BombermanGame || _buttonIndex  == SnakeGame || _buttonIndex == PongGame ){
			_buttonIndex +=2;
			_arrowMoved = 1;
			_timeMoved = GameFastTime;
		}
	}	

	if(Input->NunchuckZButton && _pageSelected == 0){
		_pageSelected = 1;
		switch(_buttonIndex){
			case BombermanGame:
				//CurrentView = new SelectGameView(LCD,Input);
			break;
			case Back:
				CurrentView = new MainMenuView(LCD,Input);
			break;
		}
	}

	if(_arrowMoved ){
		LCD->fillRect(20,20,130,80,RGB(255,0,0));
		LCD->fillRect(170,20,130,80,RGB(255,0,0));
		LCD->fillRect(20,120,130,80,RGB(255,0,0));
		LCD->fillRect(170,120,130,80,RGB(255,0,0));
		LCD->fillTriangle(50, 215 , 70, 225, 50, 235, RGB(0,0,0));
		switch(_buttonIndex){
			case BombermanGame:
				LCD->fillRect(20,20,130,80,RGB(0,255,0));
			break;
			case SnakeGame:
				LCD->fillRect(170,20,130,80,RGB(0,255,0));
			break;
			case PongGame:
				LCD->fillRect(20,120,130,80,RGB(0,255,0));				
			break;
			case Marathon:
				LCD->fillRect(170,120,130,80,RGB(0,255,0));					
			break;
			case Back:
					LCD->fillTriangle(50, 215 , 70, 225, 50, 235, RGB(0,255,0));	
			break;
			
		}
		_arrowMoved = 0;
	}

}

// default destructor
SelectGameView::~SelectGameView()
{
} //~SelectGameView
