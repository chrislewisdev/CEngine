#include <ProgramControl.h>
#include <Windows.h>
#include <gl/GL.h>
#include <iostream>

using namespace CEngine;

#undef main

class ExampleState : public State
{
public:
	ExampleState(StateMachine *_Owner) : State(_Owner) {}

	void Enter() {c = 0;}
	void Update(float deltaTime) 
	{
		glBegin(GL_POINTS);
			glVertex2f(50.0f, 50.0f);
		glEnd();

		c += 0.01f;
		std::cout << c << std::endl;
	}
	void Exit() {};
	State *Clone(StateMachine *NewOwner) const {return new ExampleState(NewOwner);}

	float c;
};

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ProgramControl Control("Example Program Control", 800, 600);

	Control.AddState(1, new ExampleState(&Control));
	Control.ChangeState(1);

	Control.GetWindow()->SetResizable(true);
	Control.SetPauseOnMinimise(true);

	while (!Control.IsExiting() && !ProgramControl::ProgramInput.GetKey(VK_ESCAPE))
	{
		Control.GetWindow()->ClearScreen();
		Control.Update(0);
		Control.GetWindow()->UpdateScreen();
	}

	return 0;
}