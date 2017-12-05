/* 
* SelectGameView.cpp
*
* Created: 30-11-2017 13:42:14
* Author: Mikena
*/


#include "SelectGameView.h"
// x 360 y 240
// default constructor
SelectGameView::SelectGameView(MI0283QT9 *LCD, InputController *inputController, Communication * communication):View(LCD, inputController,  communication)
{
	_buttonIndex = 0;
	_arrowMoved = 1;
	_pageSelected = 0;
	_timeMoved = GameFastTime;

} //SelectGameView


void SelectGameView::Load(){
	LCD->fillScreen(RGB(0,0,0));
	drawMenu();
	drawBombermanFrame();
	LCD->drawText(80,220, "Back to main", RGB(255,0,0),RGB(0,0,0),2);

	Loaded = 1;
}

void SelectGameView::drawMenu(){
	// topleft
	LCD->fillRect(20,20,5,80,RGB(255,0,0));
	LCD->fillRect(145,20,5,80,RGB(255,0,0));
	LCD->fillRect(20,20,130,5,RGB(255,0,0));
	LCD->fillRect(20,95,130,5,RGB(255,0,0));

	//topright
	LCD->fillRect(170,20,5,80,RGB(255,0,0));
	LCD->fillRect(125+170,20,5,80,RGB(255,0,0));
	LCD->fillRect(170,20,130,5,RGB(255,0,0));
	LCD->fillRect(170,95,130,5,RGB(255,0,0));
	LCD->fillRect(175,25,120,70,RGB(255,255,255));
	LCD->drawText(180,60, "Snake", RGB(0,0,255),RGB(255,255,255),1);

	LCD->fillCircle(190+60 , 49 ,3,RGB(244,176,66));
	
	LCD->fillRect(190 , 40 ,3,12,RGB(255,0,0));
	LCD->fillRect(192 , 49 ,14,3,RGB(255,0,0));

	LCD->fillRect(60+190 , 63 ,3,16,RGB(0,0,255));
	LCD->fillRect(60+190+3 , 60+16 ,14,3,RGB(0,0,255));
	LCD->fillRect(60+190+14 , 63+16 ,3,10,RGB(0,0,255));

	//bottomleft
	LCD->fillRect(20,120,5,80,RGB(255,0,0));
	LCD->fillRect(145,120,5,80,RGB(255,0,0));
	LCD->fillRect(20,120,130,5,RGB(255,0,0));
	LCD->fillRect(20,120+75,130,5,RGB(255,0,0));
	LCD->fillRect(25,125,120,70,RGB(255,255,255));		
	
	LCD->drawText(54,147, "???", RGB(0,0,255),RGB(255,255,255),3);
	//bottomright
	LCD->fillRect(170,120,5,80,RGB(255,0,0));
	LCD->fillRect(125+170,120,5,80,RGB(255,0,0));
	LCD->fillRect(170,120,130,5,RGB(255,0,0));
	LCD->fillRect(170,120+75,130,5,RGB(255,0,0));
	LCD->fillRect(175,125,120,70,RGB(255,255,255));		

	LCD->drawText(200,147, "???", RGB(0,0,255),RGB(255,255,255),3);
}

void SelectGameView::drawBombermanFrame(){
	char startX = 25;
	char startY = 30;
	char PixelSize = 2;

	LCD->fillRect(25,25,120,70,RGB(255,255,255));
	LCD->drawText(73,60, "Bomberman", RGB(0,0,255),RGB(255,255,255),1);

	LCD->fillRect(startX +(16*PixelSize), startY + (1*PixelSize),PixelSize,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(17*PixelSize), startY + (1*PixelSize),PixelSize,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(15*PixelSize), startY + (2*PixelSize),PixelSize,PixelSize,RGB(0,0,0));
	
	LCD->fillRect(startX +(17*PixelSize), startY + (2*PixelSize),PixelSize,PixelSize,RGB(237,193,210));
	LCD->fillRect(startX +(15*PixelSize), startY + (3*PixelSize),PixelSize*4,PixelSize,RGB(237,193,210));

	LCD->fillRect(startX +(18*PixelSize), startY + (2*PixelSize),PixelSize,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(14*PixelSize), startY + (3*PixelSize),PixelSize,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(19*PixelSize), startY + (3*PixelSize),PixelSize,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(14*PixelSize), startY + (4*PixelSize),PixelSize*6,PixelSize,RGB(0,0,0));
	
	LCD->fillRect(startX +(12*PixelSize), startY + (5*PixelSize),PixelSize*2,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(20*PixelSize), startY + (5*PixelSize),PixelSize*2,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(11*PixelSize), startY + (6*PixelSize),PixelSize,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(22*PixelSize), startY + (6*PixelSize),PixelSize,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(23*PixelSize), startY + (7*PixelSize),PixelSize,2*PixelSize,RGB(0,0,0));	
	LCD->fillRect(startX +(10*PixelSize), startY + (7*PixelSize),PixelSize,2*PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(13*PixelSize), startY + (7*PixelSize),PixelSize*8,2*PixelSize,RGB(217,187,123));
	LCD->fillRect(startX +(9*PixelSize), startY + (9*PixelSize),PixelSize,5*PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(24*PixelSize), startY + (9*PixelSize),PixelSize,5*PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(12*PixelSize), startY + (9*PixelSize),PixelSize,5*PixelSize,RGB(217,187,123));
	LCD->fillRect(startX +(21*PixelSize), startY + (9*PixelSize),PixelSize,5*PixelSize,RGB(217,187,123));	
	LCD->fillRect(startX +(15*PixelSize), startY + (9*PixelSize),PixelSize*4,5*PixelSize,RGB(217,187,123));
	
	LCD->fillRect(startX +(13*PixelSize), startY + (9*PixelSize),PixelSize*2,5*PixelSize,RGB(0,0,0));
	
	LCD->fillRect(startX +(14*PixelSize), startY + (10*PixelSize),PixelSize,PixelSize,RGB(255,255,255));
	LCD->fillRect(startX +(19*PixelSize), startY + (9*PixelSize),PixelSize*2,5*PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(19*PixelSize), startY + (10*PixelSize),PixelSize,PixelSize,RGB(255,255,255));
	
	LCD->fillRect(startX +(13*PixelSize), startY + (14*PixelSize),PixelSize*8,PixelSize,RGB(217,187,123));
	LCD->fillRect(startX +(14*PixelSize), startY + (15*PixelSize),PixelSize*6,PixelSize,RGB(217,187,123));
	LCD->fillRect(startX +(10*PixelSize), startY + (14*PixelSize),PixelSize,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(23*PixelSize), startY + (14*PixelSize),PixelSize,PixelSize,RGB(0,0,0));

	LCD->fillRect(startX +(11*PixelSize), startY + (15*PixelSize),PixelSize,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(22*PixelSize), startY + (15*PixelSize),PixelSize,PixelSize,RGB(0,0,0));

	LCD->fillRect(startX +(12*PixelSize), startY + (16*PixelSize),PixelSize,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(21*PixelSize), startY + (16*PixelSize),PixelSize,PixelSize,RGB(0,0,0));
	
	LCD->fillRect(startX +(19*PixelSize), startY + (17*PixelSize),PixelSize*2,PixelSize,RGB(0,0,0));
	
	LCD->fillRect(startX +(11*PixelSize), startY + (17*PixelSize),PixelSize*4,PixelSize,RGB(0,0,0));
	
	LCD->fillRect(startX +(15*PixelSize), startY + (18*PixelSize),PixelSize*4,PixelSize,RGB(0,0,0));

	LCD->fillRect(startX +(14*PixelSize), startY + (18*PixelSize),PixelSize,PixelSize,RGB(181,181,181));
	LCD->fillRect(startX +(19*PixelSize), startY + (18*PixelSize),PixelSize,PixelSize,RGB(181,181,181));
	
	LCD->fillRect(startX +(21*PixelSize), startY + (18*PixelSize),PixelSize,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(11*PixelSize), startY + (18*PixelSize),PixelSize,PixelSize,RGB(0,0,0));
	
	LCD->fillRect(startX +(10*PixelSize), startY + (19*PixelSize),4*PixelSize,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(20*PixelSize), startY + (19*PixelSize),PixelSize,PixelSize,RGB(0,0,0));
		
	LCD->fillRect(startX +(22*PixelSize), startY + (19*PixelSize),PixelSize*2,PixelSize,RGB(0,0,0));
	
	LCD->fillRect(startX +(14*PixelSize), startY + (19*PixelSize),PixelSize*2,PixelSize,RGB(0,87,168));
	LCD->fillRect(startX +(16*PixelSize), startY + (19*PixelSize),PixelSize*2,PixelSize,RGB(135,192,234));
	LCD->fillRect(startX +(18*PixelSize), startY + (19*PixelSize),PixelSize*2,PixelSize,RGB(0,87,168));
	
	LCD->fillRect(startX +(13*PixelSize), startY + (20*PixelSize),PixelSize*2,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(19*PixelSize), startY + (20*PixelSize),PixelSize*3,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(24*PixelSize), startY + (20*PixelSize),PixelSize,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(15*PixelSize), startY + (20*PixelSize),PixelSize*4,PixelSize,RGB(238,243,12));
	LCD->fillRect(startX +(22*PixelSize), startY + (20*PixelSize),PixelSize*2,PixelSize,RGB(237,193,210));
	
	LCD->fillRect(startX +(13*PixelSize), startY + (21*PixelSize),PixelSize,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(14*PixelSize), startY + (21*PixelSize),PixelSize,PixelSize,RGB(181,181,181));	
	LCD->fillRect(startX +(15*PixelSize), startY + (21*PixelSize),PixelSize*4,PixelSize,RGB(238,243,12));
	LCD->fillRect(startX +(16*PixelSize), startY + (21*PixelSize),PixelSize*2,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(19*PixelSize), startY + (21*PixelSize),PixelSize,PixelSize,RGB(181,181,181));
	LCD->fillRect(startX +(20*PixelSize), startY + (21*PixelSize),PixelSize,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(25*PixelSize), startY + (21*PixelSize),PixelSize,PixelSize*2,RGB(0,0,0));
	LCD->fillRect(startX +(21*PixelSize), startY + (21*PixelSize),PixelSize*2,PixelSize,RGB(255,0,0));
	LCD->fillRect(startX +(22*PixelSize), startY + (21*PixelSize),PixelSize*3,PixelSize,RGB(237,193,210));

	LCD->fillRect(startX +(13*PixelSize), startY + (22*PixelSize),PixelSize*2,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(15*PixelSize), startY + (22*PixelSize),PixelSize*4,PixelSize,RGB(0,87,168));
	LCD->fillRect(startX +(19*PixelSize), startY + (22*PixelSize),2*PixelSize,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(21*PixelSize), startY + (22*PixelSize),PixelSize*2,PixelSize,RGB(255,0,0));
	LCD->fillRect(startX +(22*PixelSize), startY + (22*PixelSize),PixelSize*3,PixelSize,RGB(237,193,210));
	
	LCD->fillRect(startX +(13*PixelSize), startY + (23*PixelSize),PixelSize,2*PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(14*PixelSize), startY + (23*PixelSize),PixelSize,PixelSize,RGB(181,181,181));
	LCD->fillRect(startX +(15*PixelSize), startY + (23*PixelSize),PixelSize*4,2*PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(19*PixelSize), startY + (23*PixelSize),PixelSize,PixelSize,RGB(181,181,181));

	LCD->fillRect(startX +(20*PixelSize), startY + (23*PixelSize),2*PixelSize,2*PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(22*PixelSize), startY + (23*PixelSize),2*PixelSize,PixelSize,RGB(255,0,0));
	LCD->fillRect(startX +(24*PixelSize), startY + (23*PixelSize),PixelSize,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(22*PixelSize), startY + (24*PixelSize),2*PixelSize,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(11*PixelSize), startY + (24*PixelSize),2*PixelSize,PixelSize,RGB(0,0,0));
	
	LCD->fillRect(startX +(10*PixelSize), startY + (25*PixelSize),PixelSize,PixelSize*3,RGB(0,0,0));
	LCD->fillRect(startX +(23*PixelSize), startY + (25*PixelSize),PixelSize,PixelSize*3,RGB(0,0,0));
	LCD->fillRect(startX +(16*PixelSize), startY + (25*PixelSize),PixelSize*2,PixelSize*2,RGB(0,0,0));
	LCD->fillRect(startX +(15*PixelSize), startY + (27*PixelSize),PixelSize,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(18*PixelSize), startY + (27*PixelSize),PixelSize,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(11*PixelSize), startY + (28*PixelSize),PixelSize*4,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(19*PixelSize), startY + (28*PixelSize),PixelSize*4,PixelSize,RGB(0,0,0));

	
	LCD->fillRect(startX +(14*PixelSize), startY + (25*PixelSize),PixelSize*2,PixelSize,RGB(255,0,0));
	LCD->fillRect(startX +(19*PixelSize), startY + (25*PixelSize),PixelSize*2,PixelSize,RGB(255,0,0));
	LCD->fillRect(startX +(15*PixelSize), startY + (26*PixelSize),PixelSize,PixelSize,RGB(255,0,0));
	LCD->fillRect(startX +(18*PixelSize), startY + (26*PixelSize),PixelSize,PixelSize,RGB(255,0,0));
	LCD->fillRect(startX +(13*PixelSize), startY + (27*PixelSize),PixelSize*2,PixelSize,RGB(255,0,0));
	LCD->fillRect(startX +(19*PixelSize), startY + (27*PixelSize),PixelSize*2,PixelSize,RGB(255,0,0));

	LCD->fillRect(startX +(1*PixelSize), startY + (14*PixelSize),PixelSize*2,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(1*PixelSize), startY + (15*PixelSize),PixelSize,PixelSize*3,RGB(0,0,0));
	LCD->fillRect(startX +(2*PixelSize), startY + (17*PixelSize),PixelSize,PixelSize*2,RGB(0,0,0));
	
	LCD->fillRect(startX +(3*PixelSize), startY + (16*PixelSize),PixelSize*8,PixelSize*4,RGB(0,0,0));
	LCD->fillRect(startX +(3*PixelSize), startY + (15*PixelSize),PixelSize*7,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(4*PixelSize), startY + (14*PixelSize),PixelSize*5,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(2*PixelSize), startY + (13*PixelSize),PixelSize*6,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(3*PixelSize), startY + (12*PixelSize),PixelSize*4,PixelSize,RGB(0,0,0));

	LCD->fillRect(startX +(4*PixelSize), startY + (20*PixelSize),PixelSize*7,PixelSize,RGB(0,0,0));
	LCD->fillRect(startX +(8*PixelSize), startY + (19*PixelSize),PixelSize*2,PixelSize,RGB(255,0,0));
	LCD->fillRect(startX +(9*PixelSize), startY + (18*PixelSize),PixelSize*2,PixelSize,RGB(255,0,0));
	LCD->fillRect(startX +(10*PixelSize), startY + (17*PixelSize),PixelSize,PixelSize,RGB(255,0,0));

	
	LCD->fillRect(startX +(4*PixelSize), startY + (10*PixelSize),PixelSize*2,PixelSize,RGB(181,181,181));
	LCD->fillRect(startX +(5*PixelSize), startY + (11*PixelSize),PixelSize,PixelSize,RGB(181,181,181));

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

	if(Timer % 15 == 0){
		LCD->fillRect(25 +(2*2), 30 + (7*2),2*7,2*4,RGB(255,255,255));
		LCD->fillRect(25 +(5*2), 30 + (10*2),2,2,RGB(181,181,181));
		LCD->fillRect(25 +(4*2), 30 + (10*2),2,2,RGB(255,0,0));
		LCD->fillRect(25 +(5*2), 30 + (9*2),2,2,RGB(255,0,0));
		LCD->fillRect(25 +(3*2), 30 + (10*2),2,2,RGB(255,147,28));
		LCD->fillRect(25 +(4*2), 30 + (9*2),2,2,RGB(255,147,28));
		LCD->fillRect(25 +(5*2), 30 + (8*2),2,2,RGB(255,147,28));
		LCD->fillRect(25 +(3*2), 30 + (8*2),2,2,RGB(255,147,28));
		LCD->fillRect(25 +(2*2), 30 + (10*2),2,2,RGB(238,243,12));
		LCD->fillRect(25 +(3*2), 30 + (9*2),2,2,RGB(238,243,12));
		LCD->fillRect(25 +(4*2), 30 + (8*2),2,2,RGB(238,243,12));
		LCD->fillRect(25 +(5*2), 30 + (7*2),2,2,RGB(238,243,12));
		LCD->fillRect(25 +(2*2), 30 + (8*2),2,2,RGB(238,243,12));
		LCD->fillRect(25 +(3*2), 30 + (7*2),2,2,RGB(238,243,12));
	}else if(Timer % 15 == 7){
		LCD->fillRect(25 +(2*2), 30 + (7*2),2*7,2*4,RGB(255,255,255));
		LCD->fillRect(25 +(5*2), 30 + (10*2),2,2,RGB(181,181,181));
		LCD->fillRect(25 +(6*2), 30 + (10*2),2,2,RGB(255,0,0));
		LCD->fillRect(25 +(5*2), 30 + (9*2),2,2,RGB(255,0,0));
		LCD->fillRect(25 +(7*2), 30 + (10*2),2,2,RGB(255,147,28));
		LCD->fillRect(25 +(6*2), 30 + (9*2),2,2,RGB(255,147,28));
		LCD->fillRect(25 +(5*2), 30 + (8*2),2,2,RGB(255,147,28));
		LCD->fillRect(25 +(7*2), 30 + (8*2),2,2,RGB(255,147,28));
		LCD->fillRect(25 +(8*2), 30 + (10*2),2,2,RGB(238,243,12));
		LCD->fillRect(25 +(7*2), 30 + (9*2),2,2,RGB(238,243,12));
		LCD->fillRect(25 +(6*2), 30 + (8*2),2,2,RGB(238,243,12));
		LCD->fillRect(25 +(5*2), 30 + (7*2),2,2,RGB(238,243,12));
		LCD->fillRect(25 +(8*2), 30 + (8*2),2,2,RGB(238,243,12));
		LCD->fillRect(25 +(7*2), 30 + (7*2),2,2,RGB(238,243,12));
	}

	if(Input->NunchuckZButton && _pageSelected == 0){
		_pageSelected = 1;
		switch(_buttonIndex){
			case BombermanGame:
				CurrentView = new Bomberman(GLBL_Role,GLBL_Players,LCD,Input, CommunicationHandler);
			break;
			case SnakeGame:
				CurrentView = new Snake(GLBL_Role,GLBL_Players,LCD,Input, CommunicationHandler);
			break;
			case Back:
				CurrentView = new MainMenuView(LCD,Input, CommunicationHandler);
			break;
		}
	}
	
	if(_arrowMoved ){
		drawMenu();
		LCD->fillTriangle(50, 215 , 70, 225, 50, 235, RGB(0,0,0));
		switch(_buttonIndex){
			case BombermanGame:
				LCD->fillRect(20,20,5,80,RGB(0,255,0));
				LCD->fillRect(145,20,5,80,RGB(0,255,0));
				LCD->fillRect(20,20,130,5,RGB(0,255,0));
				LCD->fillRect(20,95,130,5,RGB(0,255,0));
			break;
			case SnakeGame:
				LCD->fillRect(170,20,5,80,RGB(0,255,0));
				LCD->fillRect(125+170,20,5,80,RGB(0,255,0));
				LCD->fillRect(170,20,130,5,RGB(0,255,0));
				LCD->fillRect(170,95,130,5,RGB(0,255,0));
			break;
			case PongGame:
				LCD->fillRect(20,120,5,80,RGB(0,255,0));
				LCD->fillRect(145,120,5,80,RGB(0,255,0));
				LCD->fillRect(20,120,130,5,RGB(0,255,0));
				LCD->fillRect(20,120+75,130,5,RGB(0,255,0));			
			break;
			case Marathon:
				LCD->fillRect(170,120,5,80,RGB(0,255,0));
				LCD->fillRect(125+170,120,5,80,RGB(0,255,0));
				LCD->fillRect(170,120,130,5,RGB(0,255,0));
				LCD->fillRect(170,120+75,130,5,RGB(0,255,0));		
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
