int KHZ = 38;
int counter = 0;
int i = 0;
char Sendindx;
char Receiveindx = 0;
short sendByte;
char receiveByte;
ISR(TIMER2_COMPA_vect)
{
	if(counter==KHZ*2)	// dit zorgt ervoor dat er altijd 500x per second ontvangen worden en de byte verstuurd word
	{
		counter = 0;
		i++;
		
	if(Receiveindx != 0){
		
	}
		receiveDate();
	
		if(i>=10 && i<=20)
		{
			sendData();
			
		}
		if(i==35)
		{
					
			i=0;
		}
	}
	counter++;
}
void PWM()
{
	if(KHZ == 38){			//OCRA instellen op de gewenste frequentie
		OCR2A = 210;
		}else{
		OCR2A = 140;
	}
	DDRD |= (1<<DDD3);						//digital3 output,
	TCCR2A = (1 << COM2B1) | (1 << WGM20);	//WGM20 & WGM22 phase correct PWM
	TCCR2B = (1 << WGM22) | (1 << CS20);	//CS20 geen prescaler
	//com2b1 clear upcounting, set oc2b downcount
	OCR2B = OCR2A/2;		// 50% duty cycle
	TIMSK2 |= (1 << OCIE2A);
	sei();					//interrupt activeren
}
void receiveDate()
{
	//Serial.print(!(PINB & (1<<PORTB0)));
	
//hier word de startbit geregistreerd
	if(Receiveindx == 0 && (PINB & (1<<PORTB0))==0){
		Receiveindx++;
		receiveByte = 0;
		//Serial.println("send");
		//Serial.print(!(PINB & (1<<PORTB0)));
	}
//hier worden de bits in een short gezet
	else if(Receiveindx > 0 && Receiveindx < 10){
		
		char b = 1;
		if((PINB & (1<<PORTB0))){
			b = 0;
//als er een HIGH bit binnenkomt word deze in de short geshift
		}else{			
			receiveByte |=  b << ( Receiveindx-1);
		}
		
		//Serial.print(Receiveindx-2, DEC);
		//Serial.print(" : ");
		//Serial.println(b, DEC);
		//receiveByte |=  b << (8- Receiveindx);
//als de startbit, 8 databits en de stopbit geweest zijn is de byte ontvangen klaar
	Receiveindx++;
	} else if(Receiveindx == 10){
		Receiveindx = 0;
		Serial.println((char)(receiveByte &0xff));
	//	Serial.println(": ontvangen");
		
	}
	
}
void sendData()
{
	if(Sendindx != 10 && sendByte  != 0){
		
		short b = sendByte & (1 << Sendindx);
		b = b >> Sendindx;
		
		if(b){
			//Serial.print("1");
			// hier senden
			TCCR2A |= (1<<COM2B1);
			
			}else{
			//Serial.print("0");
			// hier uitzetten
			TCCR2A &= ~(1<<COM2B1);
			
		}
		Sendindx++;
		
	} else if (Sendindx >= 10)
	{
		// zet uit		
		TCCR2A &= ~(1<<COM2B1);
		
	}
}
//hier word de startbit en stopbit toegevoegd aan de te versturen data
void sendChar(char byt){
	sendByte = byt << 1;
	sendByte |= (1<<0) ;
	sendByte |= (1<<9);
	Sendindx = 0;
	Serial.print(sendByte,BIN);
	Serial.println(": sendbyte");

	/*while(Sendindx != 10){
	Serial.
	}*/
	

}
int main(void)
{
	DDRD |= 1<< PORTD2;
	Serial.begin(9600);
	PWM();
	
	sendByte = 0;
	
	while (1)
	{
		if(Serial.available()>0){
			sendChar(Serial.read());
		}
// 		//Serial.println("k : loop");
// 		Serial.print('k',BIN);
// 		Serial.println(": k");
// 
// 		sendChar('k');
// 		
// 		_delay_ms(4000);
	}
}





