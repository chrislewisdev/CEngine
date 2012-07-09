#include "Box2D.h"
#include "Window.h"
#include <Windows.h>
#include <iostream>
#include <gl/GL.h>

using namespace CEngine;
using namespace std;

//Helper function to draw boxes on screen- not important to the example
void DrawBox(Box2D b)
{
	glPushMatrix();
		glBegin(GL_QUADS);
			glVertex2f(b.pos.x, b.pos.y);
			glVertex2f(b.pos.x, b.pos.y + b.size.y);
			glVertex2f(b.pos.x + b.size.x, b.pos.y + b.size.y);
			glVertex2f(b.pos.x + b.size.x, b.pos.y);
		glEnd();
	glPopMatrix();
}

int main()
{
	Window MainWindow;

	MainWindow.Open("Box2D Example", 400, 300);

	glClear(GL_COLOR_BUFFER_BIT);

	//Create a simple box-constructor takes x/y position, then x/y sizes
	//Note the position values are used for the TOP LEFT of the box, not the center
	Box2D a(10, 10, 25, 25);
	DrawBox(a);

	//While boxes are considered a "step up" from Points there is no addition for Boxes
	//Naturally, what it means to "add" two boxes together is unclear!

	//Boxes provide collision detection between each other- collision should be detected for just about any possible intersection of boxes
	Box2D b(25, 25, 50, 50);
	if (b.Overlap(a))
		glColor3f(1.0f, 0.0f, 0.0f);
	DrawBox(b);

	MainWindow.UpdateScreen();

	cout << "Press enter to exit." << endl;
	cin.get();

	MainWindow.Close();

	return 0;
}