/* 
* ArduinoNunchuk.h
*
* Created: 17-11-2017 11:34:40
* Author: Mikena
*/


#ifndef __ARDUINONUNCHUK_H__
#define __ARDUINONUNCHUK_H__

#include <Arduino.h>

class ArduinoNunchuk
{
	public:
	int analogX;
	int analogY;
	int accelX;
	int accelY;
	int accelZ;
	int zButton;
	int cButton;

	void init();
	void update();

	private:
	void _sendByte(byte data, byte location);
};

#endif
