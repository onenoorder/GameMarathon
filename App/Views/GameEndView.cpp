/* 
* GameEndView.cpp
*
* Created: 7-12-2017 10:34:14
* Author: Mikena
*/


#include "GameEndView.h"

// default constructor
GameEndView::GameEndView(MI0283QT9 *LCD, InputController *inputController, Communication * communication, Player * player) :View(LCD, inputController,  communication)
{
	GamePlayer = player;
	_buttonIndex = 0;
	_arrowMoved = 1;
	_pageSelected = 1;
} //eEndView

//eindscherm laden met win of verliesgegevens.
void GameEndView::Load(){
	LCD->fillScreen(RGB(0,0,0));
	LCD->drawText(95,5, "GAME", RGB(255,0,0),RGB(0,0,0),4);
	LCD->drawText(95,40, "OVER", RGB(255,0,0),RGB(0,0,0),4);
	
	if(GamePlayer->WinState == PL_WIN)
		LCD->drawText(80,120, "You Win!", RGB(0,255,0),RGB(0,0,0),2);
	else
		LCD->drawText(80,120, "You Lose!", RGB(255,0,0),RGB(0,0,0),2);

		LCD->drawText(80,140, "Score :", RGB(255,255,0),RGB(0,0,0),1);
		LCD->drawInteger(140,140, GamePlayer->Score,DEC, RGB(255,255,0),RGB(0,0,0),1);
		
		LCD->drawText(80,200, "To Main Menu", RGB(255,0,0),RGB(0,0,0),2);
	Loaded = 1;
}


//updaten eindscherm.
void GameEndView::Update(){
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
				CurrentView = new MainMenuView(LCD,Input, CommunicationHandler);
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

