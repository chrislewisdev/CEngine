/********************************************************************
*CEngine
*GameObject.cpp by Chris Lewis
*Defines the basic functionality included in the GameObject class
********************************************************************/

#include "GameObject.h"
#include "Collision.h"
#include <Windows.h>
#include <gl/GL.h>

using namespace CEngine;

//Define our Constructor- doesn't need to do anything currently
GameObject::GameObject()
{

}

//Define our Constructor to initialise our position/size
GameObject::GameObject(Box2D boundingBox)
	: bounds(boundingBox)
{

}

//This function returns a copy of our bounding box
Box2D GameObject::BoundingBox() const
{
	return bounds;
}

//This function draws our bounding box to the screen
void GameObject::DrawBoundingBox() const
{
	glPushMatrix();
		glTranslatef(bounds.pos.x, bounds.pos.y, 0.0f);
		glBegin(GL_QUADS);
			glVertex2f(bounds.size.x, 0.0f);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(0.0f, bounds.size.y);
			glVertex2f(bounds.size.x, bounds.size.y);
		glEnd();
	glPopMatrix();
}