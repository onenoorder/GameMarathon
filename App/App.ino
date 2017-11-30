/*
 * App.ino
 *
 * Created: 11/14/2017 1:51:07 PM
 * Author: Gerhard
 */ 
#include "Communication/SerialCommunication.h"
#include "Games/Bomberman.h"
#include "Games/Snake.h"

MI0283QT9 *LCD;
Game * games[2];
InputController *inputController;
Game * CurrentGame;


ISR(TIMER2_OVF_vect) {
	CurrentGame->Timer++;
	if(CurrentGame->Timer % 5 == 0 ){
		CurrentGame->NewFrame = 1;
	}
	if (CurrentGame->Timer >= 30) {
		CurrentGame->Timer = 0;
		CurrentGame->GameTime++;
	}
}

int main(void)
{
	init();

	// set timer interrupt
	TCCR2B |= (1 << CS22) | (1<<CS21) | (1<<CS20);	//zet de klok op prescaler 1024
	TIMSK2 |= (1<<TOIE0); // zet interupt aan
	TCNT2 = 0;// zet count op 0
	sei();

	SerialCommunication *communication = new SerialCommunication();
	communication->Begin();

	LCD = new MI0283QT9();
	LCD->begin();

	inputController = new InputController();

	games[0] = new Bomberman(1, 2, LCD, inputController, communication);
	games[1] = new Snake(1, 2, LCD, inputController, communication);
	CurrentGame = games[1];

	CurrentGame->NewFrame = 1;
	CurrentGame->Load();
	while (1)
	{
		if(CurrentGame->PlayerID == 0){
			if(CurrentGame->NewFrame == 1){
				CurrentGame->Update();
			}
		} else {
			CurrentGame->Update();
		}
	}
}
