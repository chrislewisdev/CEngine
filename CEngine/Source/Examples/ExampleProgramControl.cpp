#include <ProgramControl.h>
//These following headers included for extra uses (like Windows API functionality)
#include <Windows.h>

using namespace CEngine;

//Undefine SDL's main symbol (just allows us to write our own main as normal)
#undef main

//Since ProgramControl inherits off of StateMachine, it MUST be provided a State class in order to function properly.
//Trying to call ProgramControl::Update() without having given it a State will throw an exception
//For more info on State, see ExampleStateMachine.cpp.
class ExampleState : public State
{
public:
	ExampleState(StateMachine *_Owner) : State(_Owner) {}

	void Enter() {}
	void Update(float deltaTime) 
	{
		
	}
	void Exit() {};
	State *Clone(StateMachine *NewOwner) const {return new ExampleState(NewOwner);}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//The ProgramControl has two Constructors- the one shown here will automatically set up your window upon construction.
	//The second takes no arguments and will NOT set up your window, which may be desirable if you either don't want a window
	//or want to set it up later for whatever reason.
	ProgramControl Control("Example Program Control", 800, 600);

	//As described earlier, ProgramControl must be provided a State. For more information on these see StateMachine documentation or
	//ExampleStateMachine.cpp
	Control.AddState(1, new ExampleState(&Control));
	Control.ChangeState(1);

	//The ProgramControl class houses key game classes like Window and GameData. These can each be accessed with the matching Get function.
	Control.GetWindow()->SetResizable(true);
	Control.GetGameData()->ObjectCount();

	//You can set whether or not your program should keep running while minimised. If you set PauseOnMinimise to true, everything will
	//keep running but your State Update or GameData updates will NOT be called.
	Control.SetPauseOnMinimise(true);

	//The IsExiting() function returns true when a user clicks on the Close button on your window. Naturally this is useful to control your main loop.
	//As you can see ProgramControl also houses a static instance of the InputManager class. This is so all code can access the game input regardless
	//of where from. Here it is used to make the program exit when the Escape key is pressed.
	while (!Control.IsExiting() && !ProgramControl::ProgramInput.GetKey(VK_ESCAPE))
	{
		Control.GetWindow()->ClearScreen();

		//The TimeSinceLastUpdate function does what it says- returns how long has passed (in seconds) since the last Update call.
		//This is crucial for use as the deltaTime parameter to Update should you be planning on using deltaTime in your code.
		//(after all, deltaTime is provided for a reason)
		//See StateMachine for the Update function.
		Control.Update(Control.TimeSinceLastUpdate());

		Control.GetWindow()->UpdateScreen();
	}

	return 0;
}