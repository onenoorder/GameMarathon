/* 
* View.h
*
* Created: 30-11-2017 11:21:19
* Author: Mikena
*/

#ifndef __VIEW_H__
#define __VIEW_H__

#include "../Lib/MI0283QT9/MI0283QT9.h"
#include "../Helpers/InputController.h"
#include "../Communication/Communication.h"
#include "../Model/Player.h"

#define RL_MASTER 0
#define RL_SLAVE 1

#define GLBL_Players 2
#define GLBL_Role RL_SLAVE

class View
{
public:
	unsigned char NewFrame;
	unsigned char Timer = 0;
	unsigned int GameFastTime = 0;
	unsigned int GameSeconds = 0;
	unsigned char IsGame = 0;
	MI0283QT9 * LCD;
	InputController * Input;
	Communication *CommunicationHandler;
	char Loaded;
//functions
public:
	virtual ~View(){}
	virtual void Load() = 0;
	virtual void Update() = 0;
protected:
	View(MI0283QT9 *LCD, InputController *inputController, Communication * communication);
}; //View

extern View * CurrentView;
extern Player **Players;

#endif //__VIEW_H__
