/*
 * App.ino
 *
 * Created: 11/14/2017 1:51:07 PM
 * Author: Gerhard
 */

#include "Communication/SerialCommunication.h"
#include "Games/Game.h"
#include "Games/Snake.h"
#include "Views/View.h"
#include "Views/MainMenuView.h"

MI0283QT9 *LCD;
Game * games[2];
InputController *inputController;

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
    // initieer nieuwe seriele verbinding
	SerialCommunication *communication = new SerialCommunication();
	communication->Begin();

    // maak nieuw scherm aan
	LCD = new MI0283QT9();
	LCD->begin();

    // maak een object van het type inputcontroller aan en daarmee connectie met het inputapparaat.
	inputController = new InputController(LCD);

    // maak een nieuwe 'mainmenuview' aan, het startupscherm.
	CurrentView = new MainMenuView(LCD, inputController, communication);

	// set timer interrupt
	TCCR2B |= (1 << CS22) | (1<<CS21) | (1<<CS20);	//zet de klok op prescaler 1024
	TIMSK2 |= (1<<TOIE0); // zet interupt aan
	TCNT2 = 0;// zet count op 0
	sei();
	
	while (1)
	{
        // als de currentview al geladen is, hoeft er alleen nog geupdate te worden
		if(CurrentView->Loaded)
			CurrentView->Update();
		else
			CurrentView->Load();
	}
}
