/*
 * App.ino
 *
 * Created: 11/14/2017 1:51:07 PM
 * Author: Gerhard
 */

#include "Communication/SerialCommunication.h"
#include "Communication/IRCommunication.h"
#include "Games/Game.h"
#include "Games/Snake.h"
#include "Views/View.h"
#include "Views/MainMenuView.h"

MI0283QT9 *LCD;
Game * games[2];
InputController *inputController;
int cont = 0;

ISR(TIMER2_OVF_vect) {
	if(IRCommunicationObj->Counter == IRCommunicationObj->KHZ*2)	// dit zorgt ervoor dat er altijd 500x per second ontvangen worden en de byte verstuurd word
	{
		cont++;
		if(cont== 17){
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
			cont= 0;
		}
	}
}

int main(void)
{
	init();
	
    // initieer nieuwe seriele verbinding
	Communication *communication = new SerialCommunication();
	communication->Begin();

	// maak nieuw scherm aan
	LCD = new MI0283QT9();
	LCD->begin();

    // maak een object van het type inputcontroller aan en daarmee connectie met het inputapparaat.
	inputController = new InputController(LCD);

	Players[0] = new Player();
	Players[1] = new Player();

    // maak een nieuwe 'mainmenuview' aan, het startupscherm.
	CurrentView = new MainMenuView(LCD, inputController, communication);
	
	TIMSK2 |= (1<<TOIE0); // zet interupt aan

	while (1)
	{
        // als de currentview al geladen is, hoeft er alleen nog geupdate te worden
		if(CurrentView->Loaded)
			CurrentView->Update();
		else
			CurrentView->Load();
		
	}
}