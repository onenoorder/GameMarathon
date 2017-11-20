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
	nunchuckcButton = _nunchuck->cButton;
	nunchuckzButton = _nunchuck->zButton;
	nunchuckaccelX = _nunchuck->accelX;
	nunchuckaccelY = _nunchuck->accelY;
	nunchuckaccelZ = _nunchuck->accelZ;
	nunchuckanalogX = _nunchuck->analogX;
	nunchuckanalogY = _nunchuck->analogY;
	_delay_ms(10);
	//_printInput();
}
void InputController::_printInput(){
	Serial.print("Nunchuck c : ");
	Serial.println(nunchuckcButton);

	Serial.print("Nunchuck z : ");
	Serial.println(nunchuckzButton);

	Serial.print("Nunchuck accel X : ");
	Serial.println(nunchuckaccelX);

	Serial.print("Nunchuck accel y : ");
	Serial.println(nunchuckaccelY);

	Serial.print("Nunchuck accel Z : ");
	Serial.println(nunchuckaccelZ);

	Serial.print("Nunchuck analog X : ");
	Serial.println(nunchuckanalogX);

	Serial.print("Nunchuck analog Y : ");
	Serial.println(nunchuckanalogY);
}

// default destructor
InputController::~InputController()
{
} //~InputController

