#include "Point2D.h"
#include "Window.h"
#include <Windows.h>
#include <iostream>
#include <gl/GL.h>

using namespace CEngine;
using namespace std;

//This function will draw a point to the screen- this is just helpful for illustrating our Point math
void DrawPoint(Point2D p)
{
	glPushMatrix();
		glBegin(GL_POINTS);
			glVertex2f(p.x, p.y);
		glEnd();
	glPopMatrix();
}

int main()
{
	//We create a window just for illustrating point positions
	Window MainWindow;

	MainWindow.Open("Point2D Examples", 400, 300);

	glPointSize(6.0f);

	glClear(GL_COLOR_BUFFER_BIT);

	//This is the meat of the example- showing the Point math capabilities
	//Create a simple point at (10, 10) and draw it to the screen
	Point2D a(100, 100);
	DrawPoint(a);

	//The red point shows the result of the addition between two Points
	//Addition works as a simple x1+x2, y1+y2 addition (as you'd expect)
	glColor3f(0.7f, 0.0f, 0.0f);
	Point2D b(20, 10);
	DrawPoint(a + b);

	//The green points show the use of single point components
	//The X/YComponent functions return a Point2D containing only the x/y value of that point, with 0 as the other
	glColor3f(0.0f, 0.7f, 0.0f);
	Point2D c(50, 75);
	DrawPoint(a + b + c.XComponent()); DrawPoint(a + b + c.YComponent());

	//Subtraction works as expected also
	glColor3f(0.7f, 0.0f, 0.7f);
	Point2D d(20, 20);
	DrawPoint(a - d);

	MainWindow.UpdateScreen();

	cout << "Press enter to exit.";
	cin.get();

	MainWindow.Close();

	return 0;
}