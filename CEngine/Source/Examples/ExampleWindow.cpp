#include "Window.h"
#include <Windows.h>
#include <iostream>
#include <gl/GL.h>

using namespace CEngine;

int main()
{
	//Create a Window object
	Window MainWindow;
	//Create another for additional testing
	Window SecondWindow;

	//Create the Window
	MainWindow.Open("My Test Window", 400, 300);
	//Note how the following call to open a second window throws an exception (check the console window to see)
	//Currently you can NOT have two separate windows running from the same program. This is due to how SDL handles its video systems.
	try
	{
		SecondWindow.Open("My Second Window", 500, 400);
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}

	//Set green background
	MainWindow.SetBackgroundColour(0.0f, 1.0f, 0.0f);

	//These two lines force our screen to update so we can actually see the background colour change
	glClear(GL_COLOR_BUFFER_BIT);
	MainWindow.UpdateScreen();

	//Give us 500ms to marvel at our creation
	Sleep(500);

	std::cout << "Press any key to exit.";
	std::cin.get();

	//The Window destructor will automatically close itself if still open, but of course still a good idea to close explicitly
	MainWindow.Close();

	return 0;
}