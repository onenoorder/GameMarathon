/*
 * View.cpp
 *
 * Created: 30-11-2017 11:28:09
 *  Author: Mikena
 */ 

 #include "View.h"

//
View *CurrentView = nullptr;
Player **Players = new Player*[2];

//zet
 View::View(MI0283QT9 *LCD, InputController *inputController, Communication * communication){
	this->Loaded = 0;
	this->LCD = LCD;
	this->Input = inputController;
	this->CommunicationHandler = communication;

	delete CurrentView;
	CurrentView = this;
 }

void View::Update(){
	Potmeter();
	ADCSRA |= (1<<ADSC);
	LCD->SchermResult = ADC;
	LCD->SchermResult = LCD->SchermResult>>4;
	LCD->led(LCD->SchermResult);
}
 
 void View::Potmeter(){
	 ADMUX =0; 	   		//input channel ADC1: pin A1ADMUX |= (1<<REFS0);
	 ADMUX |= (1<<REFS0);			// 5 volt
	 ADCSRA = (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);		// clock/128
	 ADCSRA |= (1<<ADEN);			//ADC enable
	 ADCSRA |= (1<<ADSC);        	//een enkele AD-conversie
 }