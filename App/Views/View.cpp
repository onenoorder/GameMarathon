/*
 * View.cpp
 *
 * Created: 30-11-2017 11:28:09
 *  Author: Mikena
 */ 

 #include "View.h"

//
 View * CurrentView = nullptr;


//zet
 View::View( MI0283QT9 *LCD, InputController *inputController, Communication * communication){
	this->Loaded = 0;
	this->LCD = LCD;
	this->Input = inputController;
	this->CommunicationHandler = communication;
 }