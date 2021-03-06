#include "Window.h"
#include <Windows.h>
#include <iostream>
#include <gl/GL.h>

using namespace CEngine;
using namespace std;

#undef main

int main()
{
	//Create a Window object
	Window MainWindow;
	//Create another for additional testing
	Window SecondWindow;

	//Trying to update a Window before it's created is invalid (same applies to SetBackgroundColour)
	try
	{
		MainWindow.UpdateScreen();
	}
	catch (std::exception& e)
	{
		cout << e.what() << endl;
	}

	//Create the Window
	MainWindow.Open("My Test Window", 400, 300);

	//Note how the following call to open a second window throws an exception (check the console window to see)
	//Currently you can NOT have two separate windows running from the same program. This is due to how SDL handles its video systems.
	try
	{
		SecondWindow.Open("My Second Window", 500, 400);
	}
	catch (std::exception& e)
	{
		cout << e.what() << endl;
	}

	//Set green background
	MainWindow.SetBackgroundColour(0.0f, 1.0f, 0.0f);

	//These two lines force our screen to update so we can actually see the background colour change
	MainWindow.ClearScreen();
	MainWindow.UpdateScreen();

	//You can toggle whether or not the window is resizable/fullscreen
	MainWindow.SetResizable(false);
	//MainWindow.SetFullscreen(false);

	//You can also directly resize the window yourself!
	MainWindow.Resize(40, 30);
	MainWindow.Resize(100, 150);

	MainWindow.ClearScreen();
	MainWindow.UpdateScreen();

	cout << "Press any key to exit.";
	cin.get();

	//The Window destructor will automatically close itself if still open, but of course still a good idea to close explicitly
	MainWindow.Close();

	return 0;
}