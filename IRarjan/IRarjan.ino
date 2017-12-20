int KHZ = 38;
int counter = 0;
int i = 0;
char Sendindx;
char Receiveindx = 0;
long int sendByte;
char receiveByte;
char receiveInvertedByte;
ISR(TIMER2_COMPA_vect)
{
	if(counter==KHZ*2)	// dit zorgt ervoor dat er altijd 500x per second ontvangen worden en de byte verstuurd word
	{
		counter = 0;
		i++;
		

		receiveDate();
		//sendData();
		
		
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

	char b = 0;
	if((PINB & (1<<PORTB0))==0){
		b = 1;
	}

	
	if(Receiveindx == 0 && (PINB & (1<<PORTB0))==0){
		Receiveindx++;

		receiveByte = 0;
		receiveInvertedByte = 0;
		
	}else if(Receiveindx >=1 && Receiveindx <=8)
	{

		receiveInvertedByte |=  b << ((Receiveindx-1));
		
		Receiveindx++;
		
	}else if(Receiveindx >=9 && Receiveindx <=16)
	{
	//	Serial.print(b,BIN );
		receiveByte |=  b << ((Receiveindx-9));
		
		Receiveindx++;
		
		} else if(Receiveindx == 17){
	//	Serial.println(b,BIN );

		Receiveindx = 0;
		if (b != 1) return;
		if(receiveByte == ~receiveInvertedByte && ~receiveByte != 0 ){
			Serial.print("Char  : ");
			Serial.println((char)(receiveByte&0xFF));
		}
		

	}
	
}
void sendData()
{
	if(Sendindx != 18 && sendByte  != 0){
		int b = 0;
		if(Sendindx != 0 && Sendindx != 17){
			b = sendByte &  (1 << Sendindx-1);
			b = b >> Sendindx-1;
		}
		if(b || (Sendindx == 0) || (Sendindx == 17)){
			//	Serial.print("1");
			// hier senden
			TCCR2A |= (1<<COM2B1);
			}else{
			//	Serial.print("0");
			// hier uitzetten
			TCCR2A &= ~(1<<COM2B1);
		}
		Sendindx++;
		
	} else if (Sendindx >= 18)
	{
		// zet uit
		TCCR2A &= ~(1<<COM2B1);
	}
}
//hier word de startbit en stopbit toegevoegd aan de te versturen data
void sendChar(char byt){
	sendByte = 0;
	sendByte |= 0x00FF & (~(byt & 0xFF) << 0);
	sendByte |=  0x00ffFF & ((byt & 0xFF) << 8);
	//	Serial.println(sendByte&0x03ffff,BIN);
	Sendindx = 0;
}
int main(void)
{
	DDRD |= 1<< PORTD2;
	Serial.begin(9600);
	PWM();
	
	sendByte = 0;
	
	while (1)
	{
		/*if(Serial.available()>0){
		sendChar(Serial.read());
		}*/


		
		/*sendChar('h');
		_delay_ms(2000);
		sendChar('o');
		_delay_ms(2000);
		sendChar('i');
		_delay_ms(2000);*/

	}
}





