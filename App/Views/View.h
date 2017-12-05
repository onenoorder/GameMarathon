/* 
* View.h
*
* Created: 30-11-2017 11:21:19
* Author: Mikena
*/


#ifndef __VIEW_H__
#define __VIEW_H__

#include "../lib/MI0283QT9/MI0283QT9.h"
#include "../Helpers/InputController.h"
class View
{
public:
	unsigned char Timer = 0;
	unsigned int GameFastTime = 0;
	unsigned int GameSeconds = 0;
	MI0283QT9 * LCD;
	InputController * Input;
	char Loaded;
//functions
public:
	virtual ~View(){}
	virtual void Load() = 0;
	virtual void Update() = 0;
protected:
	View(MI0283QT9 *LCD, InputController *inputController);
}; //View

extern View * CurrentView;

#endif //__VIEW_H__
