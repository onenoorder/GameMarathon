/*
* App.ino
*
* Created: 11/14/2017 1:51:07 PM
* Author: Gerhard
*/
#include "Communication/SerialCommunication.h"
#include "Communication/IRCommunication.h"
#include "Games/Game.h"
#include "Views/View.h"
#include "Views/MainMenuView.h"

MI0283QT9 *LCD;
Game * games[2];
InputController *inputController;
Game * CurrentGame;
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

	IRCommunication *communication = new IRCommunication();
	communication->Begin();

	communication->Send('X');


	/*_delay_ms(100);
	while(1){
		communication->Send('H');
		_delay_ms(100);
		
		Serial.print((char)communication->Receive());
	

	}*/

/*	SerialCommunication *communication = new SerialCommunication();
	communication->Begin();*/

	LCD = new MI0283QT9();
	LCD->begin();
	
	inputController = new InputController();

	CurrentView = new MainMenuView(LCD,inputController,communication);
	TIMSK2 |= (1<<TOIE0); // zet interupt aan
	// set timer interrupt
	/*TCCR2B |= (1 << CS22) | (1<<CS21) | (1<<CS20);	//zet de klok op prescaler 1024-*/


	
	while (1)
	{
		if(CurrentView->Loaded)
			CurrentView->Update();
		else
			CurrentView->Load();
		
	}
}