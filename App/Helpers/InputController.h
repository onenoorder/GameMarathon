/* 
* InputController.h
*
* Created: 17-11-2017 11:26:16
* Author: Mikena
*/


#ifndef __INPUTCONTROLLER_H__
#define __INPUTCONTROLLER_H__

#include "../Lib/ArduinoNunchuk/ArduinoNunchuk.h"

class InputController
{
//variables
public:
    int NunchuckAnalogX;
    int NunchuckAnalogY;
    int NunchuckAccelX;
    int NunchuckAccelY;
    int NunchuckAccelZ;
    int NunchuckZButton;
    int NunchuckCButton;
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
}; //InputController

#endif //__INPUTCONTROLLER_H__
