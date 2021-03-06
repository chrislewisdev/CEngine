#include <iostream>
#include "ProgramControl.h"
#include <Windows.h>

using namespace CEngine;
using namespace std;

//SDL defines its own 'main' symbol called SDL_main- if we want to use a typical main we need to undef this
#undef main

//We need to declare a default empty state for the program to use- running Update() on a State-less StateMachine is an error
class EmptyState : public State
{
public:
	EmptyState(StateMachine *Owner) : State(Owner) {}

	void Enter() {}
	void Update(float deltaTime) {}
	void Exit() {}
	State *Clone(StateMachine *NewOwner) const { return new EmptyState(NewOwner); }
};

int main()
{
	//Create a ProgramControl class to house our InputManager
	// Note how if we created a ProgramControl using the default constructor there would be no graphics window.
	// This might be preferable for some examples- especially since this one uses the console for showing text-
	// but without a graphics window to receive the 'keyboard focus' from Windows we can't actually process input at all.
	ProgramControl Control("Example InputManager", 400, 300);

	//ProgramControl must have a current State set in order to run- even if it does nothing, you have to give it something to 'do'
	Control.AddState(1, new EmptyState(&Control));
	Control.ChangeState(1);

	//Loop until the Q key is hit, or until the Close key is pressed (which will tell Control to exit)
	while (!Control.Input.GetKey('q') && !Control.IsExiting())
	{
		//You MUST call Control.Update() in order to process incoming input!!!
		Control.Update(Control.TimeSinceLastUpdate());

		//Check for various keypresses- output any pressed keys to the console
		for (char c = 'a'; c <= 'z'; c++)
		{
			if (Control.Input.GetKey(c))
			{
				cout << c << endl;
			}
		}
		//Check for directional keypresses- use the SDL defined key symbols for this
		for (int c = SDLK_UP; c <= SDLK_LEFT; c++)
		{
			if (Control.Input.GetKey(c))
			{
				//Translating the SDLK values to a string representing what it is is too much effort for an example!!
				//Besides I think the example makes its point regardless of the actual console output
				cout << "Directional Key Pressed: " << c << endl;
			}
		}
		//Number keys- note how the numpad keys are not the same as these (numpad keys are denoted SDLK_KP0 -> SDLK_KP9)
		for (int c = SDLK_0; c <= SDLK_9; c++)
		{
			if (Control.Input.GetKey(c))
			{
				cout << "Number Key Pressed: " << c << endl;
			}
		}
		//Check for mouse input buttons
		for (int mb = SDL_BUTTON_LEFT; mb <= SDL_BUTTON_RIGHT; mb++)
		{
			if (Control.Input.GetMouseDown(mb))
			{
				Vector2D position = Control.Input.GetMousePosition();
				cout << "Mouse button pressed: " << mb << " at position " << position.x << " " << position.y << endl;
			}
		}

		//Slow our application down by 30ms so the console text is a bit easier to read
		Sleep(30);
	}

	return 0;
}