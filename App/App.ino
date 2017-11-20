/*
 * App.ino
 *
 * Created: 11/14/2017 1:51:07 PM
 * Author: Gerhard
 */ 
#include "Master.h"
#include "Slave.h"
#include "Games/Bomberman.h"

MI0283QT9 *LCD;
InputController *inputController;
Game * games[1];
Game * CurrentGame;

ISR(TIMER2_OVF_vect) {
	CurrentGame->Timer++;
	if (CurrentGame->Timer >= 30) {
		CurrentGame->Timer = 0;
		CurrentGame->GameTime++;
		CurrentGame->NewFrame = 1;
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

	Serial.begin(9600);
	Master master();
	Slave slave(0);
	

	LCD = new MI0283QT9();
	LCD->begin();


	inputController = new InputController();

	games[0] = new Bomberman(LCD, inputController);
	games[0]->Load();
	CurrentGame = games[0];

	/* Replace with your application code */
	while (1)
	{
		//if(CurrentGame->NewFrame > 0)
		CurrentGame->Update();

	}
}
