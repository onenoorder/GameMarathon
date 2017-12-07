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

ISR(TIMER2_OVF_vect) {
	CurrentView->Timer++;
	if(CurrentView->IsGame && CurrentView->Timer % 5 == 0 ){
		CurrentView->NewFrame = 1;		
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

	SerialCommunication *communication = new SerialCommunication();
	communication->Begin();

	LCD = new MI0283QT9();
	LCD->begin();
	
	inputController = new InputController();

	CurrentView = new MainMenuView(LCD,inputController,communication);

	// set timer interrupt
	TCCR2B |= (1 << CS22) | (1<<CS21) | (1<<CS20);	//zet de klok op prescaler 1024
	TIMSK2 |= (1<<TOIE0); // zet interupt aan
	TCNT2 = 0;// zet count op 0
	sei();
	
	while (1)
	{	
		if(CurrentView->Loaded)
			CurrentView->Update();
		else
			CurrentView->Load();
	}
}
