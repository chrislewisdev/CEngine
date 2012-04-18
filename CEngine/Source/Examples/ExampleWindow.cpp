#include "Window.h"

using namespace CEngine;

int main()
{
	//Create a Window object
	Window MainWindow;

	//Create the Window
	MainWindow.Open("My Test Window", 400, 300);

	//Set red background
	MainWindow.SetBackgroundColour(0.0f, 1.0f, 0.0f);

	//The Window destructor will automatically close itself if still open, but of course still a good idea to close explicitly
	MainWindow.Close();

	return 0;
}