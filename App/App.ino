/*
 * App.ino
 *
 * Created: 11/14/2017 1:51:07 PM
 * Author: Gerhard
 */ 
#include "Master.h"
#include "Slave.h"
#include "Games/Bomberman.h"

Game * Currentgame;

ISR(TIMER2_OVF_vect) {
	Currentgame->Timer++;
	if (Currentgame->Timer >= 30) {
		Currentgame->Timer = 0;
		Currentgame->GameTime++;
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
	Master master();
	Slave slave(0);

	Currentgame = new Bomberman();
	Currentgame->Load();

	sei();

	/* Replace with your application code */
	while (1)
	{
		Currentgame->Update();
		_delay_ms(100);
	}
}
