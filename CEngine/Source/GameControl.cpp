/*********************************************************************
*CEngine
*GameControl.cpp by Chris Lewis
*Defines Implementation of GameControl class for GameState control
*********************************************************************/

//Include necessary headers
#include "GameControl.h"

using namespace CEngine;

//Define our main constructor
GameControl::GameControl(StateMachine *_Owner, Storage *_ObjectStorage)
	: State(_Owner), ObjectStorage(_ObjectStorage)
{

}

//Define our implementation of State::Enter- currently nothing is required
void GameControl::Enter()
{

}

//Define our implementation of State::Exit, currently nothing required
void GameControl::Exit()
{

}