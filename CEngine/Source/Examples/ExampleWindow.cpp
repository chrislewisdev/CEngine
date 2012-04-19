#include "Window.h"
#include <Windows.h>
#include <gl/GL.h>

using namespace CEngine;

int main()
{
	//Create a Window object
	Window MainWindow;

	//Create the Window
	MainWindow.Open("My Test Window", 400, 300);

	//Set green background
	MainWindow.SetBackgroundColour(0.0f, 1.0f, 0.0f);

	//These two lines force our screen to update so we can actually see the background colour change
	glClear(GL_COLOR_BUFFER_BIT);
	MainWindow.UpdateScreen();

	//Give us 500ms to marvel at our creation
	Sleep(500);

	//The Window destructor will automatically close itself if still open, but of course still a good idea to close explicitly
	MainWindow.Close();

	return 0;
}