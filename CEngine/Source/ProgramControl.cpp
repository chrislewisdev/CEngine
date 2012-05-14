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
	: exit(false), ticks(GetTickCount())
{
	MainWindow.Open(title, width, height);
}

//This function updates our overall program states
void ProgramControl::Update(float deltaTime)
{
#pragma message("TODO: ProgramControl::Update")

	//Process Window Messages
	SDL_Event windowEvent;
	//Loop as long as we have messages
	while (SDL_PollEvent(&windowEvent))
	{
		//Pass the message through Input first to see if it's an input event
		if (!InputControl.ProcessEvent(windowEvent))
		{
			//If it's not input, handle it here
			if (windowEvent.type == SDL_QUIT)
			{
				exit = true;
			}
			//Should handle a resize event too
		}
	}

	//Do a Batch Add on our Game Data

	StateMachine::Update(deltaTime);

	//Do a Batch Remove on our Game Data

	//Update our ticks counter
	ticks = GetTickCount();
}

//This function returns the time passed since our last update
float ProgramControl::TimeSinceLastUpdate() const
{
#pragma message("TODO: ProgramControl::TimeSinceLastUpdate- Check accuracy")

	return (GetTickCount() - ticks) / 1000.0f;
}

//This function returns a pointer to our Game Data instance
GameData *ProgramControl::GetGameData()
{
	return &Storage;
}

//This function returns a pointer to our Window instance
Window *ProgramControl::GetWindow()
{
	return &MainWindow;
}

//This function checks if we're trying to close or not
bool ProgramControl::IsExiting() const
{
	return exit;
}