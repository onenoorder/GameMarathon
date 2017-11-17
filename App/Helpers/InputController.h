/* 
* InputController.h
*
* Created: 17-11-2017 11:26:16
* Author: Mikena
*/
#include "../lib/ArduinoNunchuk/ArduinoNunchuk.h"

#ifndef __INPUTCONTROLLER_H__
#define __INPUTCONTROLLER_H__


class InputController
{
//variables
public:
    int nunchuckanalogX;
    int nunchuckanalogY;
    int nunchuckaccelX;
    int nunchuckaccelY;
    int nunchuckaccelZ;
    int nunchuckzButton;
    int nunchuckcButton;
protected:
private:
ArduinoNunchuk * _nunchuck;

//functions
public:
	InputController();
	~InputController();
	void UpdateInput();
protected:
private:
	InputController( const InputController &c );
	InputController& operator=( const InputController &c );
	void _printInput();
}; //InputController

#endif //__INPUTCONTROLLER_H__
