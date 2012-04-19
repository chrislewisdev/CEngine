/*************************************************************
*CEngine
*StateMachine.h by Chris Lewis
*Declares class StateMachine for handling control/ownership of object States
*************************************************************/

#ifndef CENGINE_STATEMACHINE_H
#define CENGINE_STATEMACHINE_H

//Include headers as necessary
#include "State.h"
#include <map>
#include <boost/shared_ptr.hpp>

//Declare inside the CEngine namespace
namespace CEngine
{
	/// \brief Controls storage, handling and operation of States in an object
	///
	/// The StateMachine class handles all States designated to it. New States must be added by passing a new'd State instance
	/// to AddState after its ID value. The ID values you set can be used from then on to identify current states and designate
	/// state changes.
	/// Once a State is added the StateMachine is considered to have full ownership of it. It will be automatically deleted once the StateMachine
	/// is destroyed and must not be tampered with by anything else.
	/// Once set up a StateMachine should naturally be used for handling all Updates of the object it is responsible for.
	class StateMachine
	{
	public:
		//! Default Constructor- no initialisations necessary
		StateMachine();

		//Declare a typdef for our State Pointer type
		typedef boost::shared_ptr<State> StatePointer;

		//Declare public functions
		/// \brief Adds a new state to our StateMachine
		///
		/// \param id The integer ID to use for the State (must be unique)
		/// \param NewState Pointer to a state instance to use as the new state. This must be created with keyword new.
		/// \return void
		void AddState(int id, StatePointer NewState);
		/// \brief Changes the current state to that with the specified ID
		///
		/// \param id ID value of the state to change to
		/// \return void
		void ChangeState(int id);
		/// \brief Returns the current state ID
		/// \return An int representing the current state
		int CurrentState() const;
		/// \brief Updates our Current State
		///
		/// \param deltaTime The time to have passed since the last update
		/// \return void
		void Update(float deltaTime);

	private:
		//Declare a typedef for our choice of State storage
		typedef std::map<int, StatePointer > StateCollection;

		//Declare private properties
		//State map storage
		StateCollection States;
		//Current-State pointer and ID value
		State *CurrentState;
		int CurrentStateID;
	};
}

#endif