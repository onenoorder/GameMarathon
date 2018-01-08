/* 
* Game.cpp
*
* Created: 14-11-2017 13:53:46
* Author: Gerhard
*/

#include "Game.h"

//constructor voor aanmaken object van het type game
Game::Game(MI0283QT9 *LCD, InputController *inputController, Communication *communication) :View(LCD, inputController, communication) {
	IsGame = 1;
	NewFrame = 0;
	PlayerID = GLBL_Role;
	PlayerCount = GLBL_Players;
	EndTime = 0;
	TransitionCounter = 0;
}

//updaten game, frame reset.
void Game::Update(){
	View::Update();
	NewFrame = 0;
}

//update spelers en verstuur data
void Game::UpdatePlayers(){
	if(PlayerID == 0){
		CommunicationHandler->Send(GetOutputData());

		if(PlayerCount > 1)
			DoInputData(CommunicationHandler->Receive());
	} else {
		if(PlayerCount > 1)
			DoInputData(CommunicationHandler->Receive());
		
		CommunicationHandler->Send(GetOutputData());
	}
}

// virtual destructor
Game::~Game()
{
} //~Game
