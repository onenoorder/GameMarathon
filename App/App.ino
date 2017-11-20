/*
 * App.ino
 *
 * Created: 11/14/2017 1:51:07 PM
 * Author: Gerhard
 */ 
#include "Communication/Master.h"
#include "Communication/Slave.h"
#include "Games/Bomberman.h"

MI0283QT9 *LCD;
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

	Serial.begin(9600);
	
	sei();
	LCD = new MI0283QT9();
	LCD->begin();
	games[0] = new Bomberman(0, LCD);
	games[0]->Load();
	CurrentGame = games[0];

	/* Replace with your application code */
	while (1)
	{
		//if(CurrentGame->NewFrame > 0)
		CurrentGame->Update();

	}
}
