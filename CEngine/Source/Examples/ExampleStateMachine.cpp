#include "StateMachine.h"
#include <iostream>
#include <string>

using namespace CEngine;
using namespace std;

//Declare an enum to use for State IDs- there are various ways you could keep your IDs but I consider enums a good starting point
enum StateIDs
{
	GameState, MenuState, WhateverState
};

//Define an example State class
class ExampleState: public State
{
public:
	//The constructor must take an 'Owner' parameter to pass to the base Constructor
	ExampleState(StateMachine *Owner, string msg) : State(Owner), message(msg) {};
	~ExampleState() {}

	//The Enter function is run when entering into a state
	void Enter() {cout << "Entering state: " << message << endl;}
	//The Update function is called by you when you call StateMachine::Update
	void Update(float deltaTime) {cout << "Updating state: " << message << endl;}
	//The Exit function is called before transitioning into a new state
	void Exit() {cout << "Exiting state: " << message << endl;}

private:
	string message;
};

int main()
{
	//Create a new StateMachine object
	StateMachine Game;

	//Add new StatePointers with a newly constructed State instance- the StateMachine will take ownership of the State and automatically delete it
	Game.AddState(GameState, StatePointer(new ExampleState(&Game, "Playing the game.")));
	Game.AddState(MenuState, StatePointer(new ExampleState(&Game, "Viewing the menu.")));
	Game.AddState(WhateverState, StatePointer(new ExampleState(&Game, "Doing whatever.")));

	//Changing to a new state will trigger its Enter method and then we can update it
	Game.ChangeState(GameState);
	Game.Update(5);

	//Changing into another state will trigger the Exit/Enter methods of the appropriate States
	Game.ChangeState(MenuState);
	Game.Update(5);

	//GetCurrentState returns the integer ID for the current state
	cout << "Current State: " << Game.GetCurrentState() << endl;

	Game.ChangeState(WhateverState);
	Game.Update(5);

	cout << "Press any key to exit.";
	cin.get();

	return 0;
}