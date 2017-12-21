/*
* IRCommunication.cpp
*
* Created: 13-12-2017 14:04:34
* Author: Mikena
*/

#include "IRCommunication.h"

IRCommunication *IRCommunicationObj = 0;

// default constructor
IRCommunication::IRCommunication()
{
	IRCommunicationObj = this;
} //IRCommunication

void IRCommunication::Begin(){
	DDRD |= 1<< PORTD2;
	_sendByte = 0;

	if(KHZ == 38){			//OCRA instellen op de gewenste frequentie
		OCR2A = 210;
	} else{
		OCR2A = 140;
	}
	DDRD |= (1<<DDD3);						//digital3 output,
	TCCR2A = (1 << COM2B1) | (1 << WGM20);	//WGM20 & WGM22 phase correct PWM
	TCCR2B = (1 << WGM22) | (1 << CS20);	//CS20 geen prescaler
	//com2b1 clear upcounting, set oc2b downcount
	OCR2B = OCR2A/2;		// 50% duty cycle
	TIMSK2 |= (1 << OCIE2A);
	sei();					//interrupt activeren
	Serial.begin(9600);
}

void IRCommunication::Send(unsigned char data){

	_sendByte = 0;
			Serial.print("d:");
			Serial.println(data,BIN);
	_sendByte |= 0x00FF & (~(data & 0xFF) << 0);
	_sendByte |=  0x00ffFF & ((data & 0xFF) << 8);

		Serial.print("s:");
		Serial.println(_sendByte,BIN);
	_sendIndex = 0;
}

unsigned char IRCommunication::Receive(){
	while(_inputData == 0)
		_delay_ms(1);

	unsigned char ReturnValue = _inputData;
	_inputData = 0;

	return ReturnValue;
}
// default destructor
IRCommunication::~IRCommunication()
{
} //~IRCommunication

void IRCommunication::ReceiveData()
{
	char b = 0;
	if((PIND & (1<<PORTD4))==0)
	b = 1;

	//Serial.print(b,DEC);
	if(_receiveIndex == 0 && (PIND & (1<<PORTD4))==0){
		_receiveIndex++;
		_receiveByte = 0;
		_receiveInvertedByte = 0;
	} else if(_receiveIndex >=1 && _receiveIndex <=8){
		_receiveInvertedByte |=  b << ((_receiveIndex-1));
		_receiveIndex++;
	} else if(_receiveIndex >=9 && _receiveIndex <=16){
		_receiveByte |=  b << ((_receiveIndex-9));
		_receiveIndex++;
	} else if(_receiveIndex == 17){
		_receiveIndex = 0;
		Serial.print("r:");
		Serial.println(_receiveByte,BIN);
		if (b != 1) return;
		if(_receiveByte == ~_receiveInvertedByte && ~_receiveByte != 0)
			_inputData = (unsigned char)(_receiveByte&0xFF);
	}
}

void IRCommunication::SendData()
{
	if(_sendIndex != 18 && _sendByte != 0){
		int b = 0;
		if(_sendIndex != 0 && _sendIndex != 17){
			b = _sendByte &  (1 << _sendIndex-1);
			b = b >> _sendIndex-1;
		}
		if(b || (_sendIndex == 0) || (_sendIndex == 17)){
			// hier senden
			TCCR2A |= (1<<COM2B1);
		} else {
			// hier uitzetten
			TCCR2A &= ~(1<<COM2B1);
		}
		_sendIndex++;
		
	} else if (_sendIndex >= 18)
	{
		// zet uit
		TCCR2A &= ~(1<<COM2B1);
	}
}

ISR(TIMER2_COMPA_vect)
{

	if(IRCommunicationObj->Counter == IRCommunicationObj->KHZ*2)	// dit zorgt ervoor dat er altijd 500x per second ontvangen worden en de byte verstuurd word
	{
		

		IRCommunicationObj->Counter = 0;
		IRCommunicationObj->SubCounter++;

		IRCommunicationObj->ReceiveData();
		IRCommunicationObj->SendData();
		
		if(IRCommunicationObj->SubCounter == 35)
		{
			IRCommunicationObj->SubCounter = 0;
		}
	}
	IRCommunicationObj->Counter++;
}