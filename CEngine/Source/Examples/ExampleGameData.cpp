#include <iostream>
#include "ProgramControl.h"
#include "GameObject.h"
#include "GameState.h"

using namespace CEngine;
using namespace std;

//SDL defines a main symbol as SDL_main- to use a typical main we must undef this symbol
#undef main

//Define an example GameObject
class ExampleObject : public GameObject
{
public:
	void Update(float deltaTime)
	{
		cout << "Example Object being updated!" << endl;
	}
};

//Define an example Game State
class ExampleState : public GameState
{
public:
	ExampleState(StateMachine *_Owner, GameData *_Storage) : GameState(_Owner, _Storage) {}

	void Enter() {}
	void Update(float deltaTime)
	{
		//GameData's RemoveObject function takes a GameObjectCollection::iterator referencing the object to be removed
		//The overload of RemoveObject used here removes a range of iterators from the game (in this case, the entire collection)
		//Note how, even if we remove all objects during the state, they will still exist for the duration of this update
		//GameStorage->RemoveObject(GameStorage->Begin(), GameStorage->End());

		//Emits an Update message for all objects
		//Use the Begin and End functions to iterate through the GameObjects just like any old container
		for (GameObjectCollection::iterator cdtr = GameStorage->Begin(); cdtr != GameStorage->End(); cdtr++)
		{
			(*cdtr)->Update(deltaTime);
		}
	}
	void Exit() {}
	State *Clone(StateMachine *NewOwner) const
	{
		return new ExampleState(NewOwner, GameStorage);
	}
};

int main()
{
	//Declare a ProgramControl instance as it houses our Game Data
	//Using the default constructor does not create a window so we can have a simpler example
	ProgramControl Control;

	//Add our example game state into the program
	Control.AddState(1, StatePointer(new ExampleState(&Control, Control.GetGameData())));
	Control.ChangeState(1);

	//Retrieve our GameData handle
	GameData *Storage = Control.GetGameData();

	//The GameData class is designed to help protect against various accidents that can happen when adding/removing objects.
	//However, it doesn't protect against everything. If you pass an invalid iterator to RemoveObject, it will most likely crash.
	//Avoiding that shouldn't be terribly difficult though, provided you work only off game objects existing in the GameData class, and
	//don't conjur any arbitrary references out of mid-air.
	//RemoveObject will check for any objects that have already been requested for deletion so you don't need to worry about double-removing
	//a single object.
	//Also, due to the nature of how objects are added into the game, it should be nigh on impossible to encounter any situation where you add
	//an object into the game state, but then request it be deleted before it's properly added in (since you have no idea what the iterator
	//referencing that object will be until it is ACTUALLY in the game).

	//Add some game objects into the game
	Storage->AddObject(GameObjectPointer(new ExampleObject()));
	Storage->AddObject(GameObjectPointer(new ExampleObject()));
	Storage->AddObject(GameObjectPointer(new ExampleObject()));

	//Note how if you inspect the current no. of game objects NOW, the count will be 0
	//This is because objects are not added/removed until a batch add/remove is performed
	//Batch additions/removals are performed by the ProgramControl class when you run an Update
	//This guarantees that, during a single GameState Update, the GameObjects currently in the game is constant
	//This is an important thing to keep in mind when designing your game logic
	cout << "Game Objects Before State Update: " << Storage->ObjectCount() << endl;

	//If you uncomment the 'RemoveObject' line in ExampleState, the second Update will output nothing
	Control.Update(Control.TimeSinceLastUpdate());
	cout << endl;
	Control.Update(Control.TimeSinceLastUpdate());

	cin.get();

	//Naturally, the GameData class clears out all its objects when it is destroyed

	return 0;
}