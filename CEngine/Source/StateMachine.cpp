/*******************************************************************
*CEngine
*StateMachine.cpp by Chris Lewis
*Implementation file for class StateMachine
*******************************************************************/

//Include necessary headers
#include "StateMachine.h"

using namespace CEngine;

//Define our Default Constructor
StateMachine::StateMachine()
	: CurrentState(NULL), CurrentStateID(-1)
{

}

//This function inserts a new state into our storage with the specified ID
void StateMachine::AddState(unsigned int id, StatePointer State)
{
	if (!State)
		throw NullStateException("StateMachine::AddState was passed a null pointer.");

	if (States.find(id) != States.end())
		throw DuplicateStateIDException("Attempted to add a State with an existing ID number.");

	States.insert(std::pair<int, StatePointer>(id, State));
}

//This function sets our State to that with the specified ID
void StateMachine::ChangeState(unsigned int id)
{
	//Check the desired State exists before we do anything
	if (States.find(id) == States.end()) throw NullStateException("No State corresponds to the supplied ID.");

	//Transition to the new state
	if (CurrentState) CurrentState->Exit();
	CurrentState = States.find(id)->second.get();
	CurrentState->Enter();

	CurrentStateID = id;
}

//This function returns our Current State ID
int StateMachine::GetCurrentState() const
{
	return CurrentStateID;
}

//This function updates our current state
void StateMachine::Update(float deltaTime)
{
	if (CurrentState)
		CurrentState->Update(deltaTime);
	else
		throw NullStateException("StateMachine::Update was called without a valid State set.");
}