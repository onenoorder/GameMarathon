/* 
* InputController.h
*
* Created: 17-11-2017 11:26:16
* Author: Mikena
*/

#ifndef __INPUTCONTROLLER_H__
#define __INPUTCONTROLLER_H__

#include "../Lib/ArduinoNunchuk/ArduinoNunchuk.h"
#include "../Lib/MI0283QT9/MI0283QT9.h"

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
    int LCDTouchX;
    int LCDTouchY;
protected:
private:
ArduinoNunchuk * _nunchuck;
MI0283QT9 * _LCD;

//functions
public:
	InputController(MI0283QT9 *LCD);
	~InputController();
	void UpdateInput();
protected:
private:
}; //InputController

#endif //__INPUTCONTROLLER_H__
