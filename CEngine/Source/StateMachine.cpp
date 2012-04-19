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
void StateMachine::AddState(int id, StatePointer State)
{
	States.insert(std::pair<int, StatePointer>(id, State));
}

//This function sets our State to that with the specified ID
void StateMachine::ChangeState(int id)
{
	//Retrieve new State
	State *NewState = States.at(id).get();

	//Transition to the new state
	CurrentState->Exit();
	CurrentState = NewState;
	CurrentState->Enter();
}

//This function returns our Current State ID
int StateMachine::CurrentState() const
{
	return CurrentStateID;
}

//This function updates our current state
void StateMachine::Update(float deltaTime)
{
	CurrentState->Update(deltaTime);
}