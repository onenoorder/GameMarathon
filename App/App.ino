/*
 * App.ino
 *
 * Created: 11/14/2017 1:51:07 PM
 * Author: Gerhard
 */ 
#include "Communication/SerialCommunication.h"
#include "Games/Bomberman.h"
#include "Games/Snake.h"
#include "Views/View.h"
#include "Views/MainMenuView.h"

MI0283QT9 *LCD;
Game * games[2];
InputController *inputController;
Game * CurrentGame;
char gameStarted; //hotfix

ISR(TIMER2_OVF_vect) {
	CurrentView->Timer++;
	if(gameStarted && CurrentView->Timer % 5 == 0 ){
		CurrentGame->NewFrame = 1;
	}
	if (CurrentView->Timer % 10 == 0) {
		CurrentView->GameFastTime++;
	}
	if (CurrentView->Timer >= 30) {
		CurrentView->Timer = 0;
		CurrentView->GameSeconds++;
	}
}

int main(void)
{
	init();
	gameStarted = 0;
	
	SerialCommunication *communication = new SerialCommunication();
	communication->Begin();

	LCD = new MI0283QT9();
	LCD->begin();
	
	inputController = new InputController();

	CurrentView = new MainMenuView(LCD,inputController);

	// set timer interrupt
	TCCR2B |= (1 << CS22) | (1<<CS21) | (1<<CS20);	//zet de klok op prescaler 1024
	TIMSK2 |= (1<<TOIE0); // zet interupt aan
	TCNT2 = 0;// zet count op 0
	sei();

	games[0] = new Bomberman(0, 1, LCD, inputController, communication);
	games[1] = new Snake(1, 2, LCD, inputController, communication);

	CurrentGame = games[0];
	CurrentGame->NewFrame = 1;

	CurrentGame->Load();
	while (1)
	{	
		/*if(CurrentView->Loaded)
			CurrentView->Update();
		else
			CurrentView->Load();*/
		
		/*if(CurrentGame->PlayerID == 0){
			if(CurrentGame->NewFrame == 1){
				CurrentGame->Update();
			}
		} else {*/
			CurrentGame->Update();
			CurrentGame->Timer++;
			CurrentGame->GameFastTime++;
			CurrentGame->GameSeconds++;
			delay(200);

		//}
	}
}
