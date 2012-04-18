/*************************************************************
*CEngine
*StateMachine.h by Chris Lewis
*Declares class StateMachine for handling control/ownership of object States
*************************************************************/

#ifndef CENGINE_STATEMACHINE_H
#define CENGINE_STATEMACHINE_H

//Include headers as necessary
#include <map>
#include <boost/shared_ptr.hpp>

//Temporary forward declaration
class State;

//Declare inside the CEngine namespace
namespace CEngine
{
	/// \brief Controls storage, handling and operation of States in an object
	///
	/// TODO: FUNCTIONS AND STUFF
	class StateMachine
	{
	public:
		//! Default Constructor- no initialisations necessary
		StateMachine();

	private:
		//Declare private properties
		//State map storage
		std::map<int, boost::shared_ptr<State> > States;
		//Current-State pointer
		State *CurrentState;
	};
}

#endif