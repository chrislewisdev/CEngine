/******************************************************************
*CEngine
*ProgramControl.cpp by Chris Lewis
*Implementation file for Program Control class, foundation of program flow
******************************************************************/

#include "ProgramControl.h"

using namespace CEngine;

//Define our static ProgramControl variables
Input ProgramControl::InputControl;
const Input const *ProgramControl::ProgramInput = &ProgramControl::InputControl;

//Constructor creates a new window on creation- nothing else needs to be initialised
ProgramControl::ProgramControl(const char *title, int width, int height)
{
	MainWindow.Open(title, width, height);
}

//This function updates our overall program states
void ProgramControl::Update(float deltaTime)
{
	//TODO
#pragma message("TODO: ProgramControl::Update")

	//Process Window Messages

	//Do a Batch Add on our Game Data

	StateMachine::Update(deltaTime);

	//Do a Batch Remove on our Game Data
}

//This function returns the time passed since our last update
float ProgramControl::TimeSinceLastUpdate() const
{
	//TODO
#pragma message("TODO: ProgramControl::TimeSinceLastUpdate")
	return 5.0f;
}

//This function returns a pointer to our Game Data instance
GameData *ProgramControl::GetGameData()
{
	return &Storage;
}