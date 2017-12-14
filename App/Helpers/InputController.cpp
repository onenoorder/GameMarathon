/* 
* InputController.cpp
*
* Created: 17-11-2017 11:26:16
* Author: Mikena
*/


#include "InputController.h"

// default constructor
InputController::InputController()
{
	_nunchuck = new ArduinoNunchuk();
	_nunchuck->init();
	UpdateInput();
} //InputController

void InputController::UpdateInput(){
	_nunchuck->update();

	NunchuckCButton = _nunchuck->cButton;
	NunchuckZButton = _nunchuck->zButton;
	NunchuckAccelX = _nunchuck->accelX;
	NunchuckAccelY = _nunchuck->accelY;
	NunchuckAccelZ = _nunchuck->accelZ;
	NunchuckAnalogX = _nunchuck->analogX;
	NunchuckAnalogY = _nunchuck->analogY;
	_delay_ms(10);
	//_printInput();
}

// default destructor
InputController::~InputController()
{
	delete[] _nunchuck;
} //~InputController

