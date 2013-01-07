/******************************************************************
*CEngine
*ProgramControl.cpp by Chris Lewis
*Implementation file for Program Control class, foundation of program flow
******************************************************************/

#include "ProgramControl.h"
#include <SDL.h>

using namespace CEngine;

//Define our static ProgramControl variables
ProgramControl *ProgramControl::instance = NULL;

//Constructor creates a new window on creation- nothing else needs to be initialised
ProgramControl::ProgramControl(const char *title, int width, int height)
	: exit(false), active(true), pauseWhenInactive(false), inputFocus(true), Input(InputControl), Resources(ResourcesControl)
{
	//Enforce that this is a singleton
	if (instance == NULL)
	{
		instance = this;
	}
	else
	{
		throw SingletonViolationException("You must not instantiate multiple objects of ProgramControl");
	}

	MainWindow.Open(title, width, height);
	if (SDL_InitSubSystem(SDL_INIT_TIMER) == -1)
	{
		throw Window::InitException("SDL Initialisation failed.");
	}
	ticks = SDL_GetTicks();
}

//Constructor that doesn't open a window
ProgramControl::ProgramControl()
	: exit(false), Input(InputControl), Resources(ResourcesControl)
{
	//Enforce that this is a singleton
	if (instance == NULL)
	{
		instance = this;
	}
	else
	{
		throw SingletonViolationException("You must not instantiate multiple objects of ProgramControl");
	}

	if (SDL_Init(SDL_INIT_TIMER) == -1)
	{
		throw Window::InitException("SDL Initialisation failed.");
	}
	ticks = SDL_GetTicks();
}

//Destructor
ProgramControl::~ProgramControl()
{
	instance = NULL;
}

//This function returns our singleton instance reference
ProgramControl& ProgramControl::Instance()
{
	return *instance;
}

//This function updates our overall program states
void ProgramControl::Update(float deltaTime)
{
	//Process Window Messages
	SDL_Event windowEvent;
	//Loop as long as we have messages
	while (SDL_PollEvent(&windowEvent))
	{
		//Pass the message through InputManager first to see if it's an input event
		if (!InputControl.ProcessEvent(windowEvent))
		{
			//If it's not input, handle it here
			if (windowEvent.type == SDL_QUIT)
			{
				exit = true;
			}
			else if (windowEvent.type == SDL_VIDEORESIZE)
			{
				//Window resizing (will only do so if enabled)
				MainWindow.Resize(windowEvent.resize.w, windowEvent.resize.h);
			}
			else if (windowEvent.type == SDL_ACTIVEEVENT)
			{
				//Minimise/restore or input loss events
				if (windowEvent.active.state & SDL_APPACTIVE) active = (windowEvent.active.gain == 1);
				if (windowEvent.active.state & SDL_APPINPUTFOCUS) inputFocus = (windowEvent.active.gain == 1);
			}
		}
	}

	//Update our ticks counter
	ticks = SDL_GetTicks();

	//Don't run the game if we're minimised and set to pause on minimisation
	if ((active && inputFocus) || !pauseWhenInactive)
	{
		//Do a Batch Add on our Game Data
		Storage.PerformBatchAdd();

		StateMachine::Update(deltaTime);

		//Do a Batch Remove on our Game Data
		Storage.PerformBatchRemove();
	}
}

//This function returns the time passed since our last update
float ProgramControl::TimeSinceLastUpdate() const
{
	return (SDL_GetTicks() - ticks) / 1000.0f;
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

//This function toggles program pausing while minimised
void ProgramControl::SetPauseOnMinimise(bool pause)
{
	pauseWhenInactive = pause;
}