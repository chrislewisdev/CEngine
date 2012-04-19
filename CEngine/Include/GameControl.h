/****************************************************************
*CEngine
*GameControl.h by Chris Lewis
*Declares GameControl, an implementation of both State and StateMachine
****************************************************************/

#ifndef CENGINE_GAMECONTROL_H
#define CENGINE_GAMECONTROL_H

//Include related headers
#include "State.h"
#include "StateMachine.h"

//Declare inside CEngine namespace
namespace CEngine
{
	//Forward-declare Storage class
	class Storage;

	/// \brief Implementation of both State and StateMachine for controlling game logic.
	///
	/// The GameControl class inherits off of both State and StateMachine- that is to say, it is a StateMachine that can be used as a state
	/// of the broader program control. This allows the game-state to be its own distinct State in the program whilst still being able
	/// to have its own States as necessary. Calling Update essentially runs StateMachine::Update.
	class GameControl : virtual public State, public StateMachine
	{
	public:
		//! Main constructor to take a pointer to our Storage object
		GameControl(StateMachine *_Owner, Storage *_ObjectStorage);

		//Declare public functions
		//! Concretion of State::Enter()- does nothing
		void Enter();
		//! Concretion of State::Exit()- does nothing
		void Exit();

	private:
		//Declare private properties
		//Pointer to our Storage instance
		Storage *ObjectStorage;
	};
}

#endif