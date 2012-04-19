/******************************************************************
*CEngine
*GameState.h by Chris Lewis
*Defines abstract subclass of State specific to Game control
*******************************************************************/

#ifndef CENGINE_GAMESTATE_H
#define CENGINE_GAMESTATE_H

//Include State header
#include "State.h"
#include "GameControl.h"

//Declare inside the CEngine namespace
namespace CEngine
{
	/// \brief Abstract class as a slight expansion of State to use for Game Logic control
	///
	/// The GameState class inherits off of State and has no added members besides a pointer to its owning GameControl class, which
	/// allows access specific to the game objects.
	class GameState : public State
	{
	public:
		//! Single constructor to initialise our Game Owner
		GameState(GameControl *_GameOwner) : State(_GameOwner), GameOwner(_GameOwner) {};

	protected:
		//Declare protected members
		//! Pointer to our owning GameControl object
		GameControl *GameOwner;
	}
}

#endif