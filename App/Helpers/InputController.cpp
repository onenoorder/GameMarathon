/* 
* InputController.cpp
*
* Created: 17-11-2017 11:26:16
* Author: Mikena
*/

#include "InputController.h"
#include "../Views/View.h"

// default constructor, maakt nieuw object van type ArduinoNunchuck aan, initieert deze en laadt nieuwe waardes (update);
InputController::InputController(MI0283QT9 *LCD)
{
	NunchuckAnalogX = 0;
	NunchuckAnalogY = 0;
	NunchuckAccelX = 0;
	NunchuckAccelY = 0;
	NunchuckAccelZ = 0;
	NunchuckZButton = 0;
	NunchuckCButton = 0;
	LCDTouchX = 0;
	LCDTouchY = 0;

	_nunchuck = new ArduinoNunchuk();
	_nunchuck->init();
	_LCD = LCD;
} //InputController

//lees nieuwe waarden van controller uit(update)
void InputController::UpdateInput(){
	_nunchuck->update();
	
	NunchuckCButton = _nunchuck->cButton;
	NunchuckZButton = _nunchuck->zButton;
	NunchuckAccelX = _nunchuck->accelX;
	NunchuckAccelY = _nunchuck->accelY;
	NunchuckAccelZ = _nunchuck->accelZ;
	NunchuckAnalogX = _nunchuck->analogX;
	NunchuckAnalogY = _nunchuck->analogY;

	_LCD->touchRead();
	LCDTouchX = _LCD->tp_x;
	LCDTouchY = _LCD->tp_y;
	_LCD->tp_x = 0;
	_LCD->tp_y = 0;

	_delay_ms(20);
	//_printInput();
}

// default destructor
InputController::~InputController()
{
	delete[] _nunchuck;
} //~InputController

