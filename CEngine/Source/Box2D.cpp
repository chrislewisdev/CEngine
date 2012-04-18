/******************************************************************
*CEngine
*Box2D.cpp by Chris Lewis
*Implementation file of Box2D struct
******************************************************************/

//Include necessary headers
#include "Box2D.h"

using namespace CEngine;

//Define our default constructor
Box2D::Box2D()
{

}

//Constructor to take position/size
Box2D::Box2D(Point2D p, Size2D s)
	: pos(p), size(s)
{

}

//Constructor to take individual position/size values
Box2D::Box2D(float x, float y, float xSize, float ySize)
	: pos(x, y), size(x, y)
{

}

//This function checks for a point collision inside our box
bool Box2D::BoxCollision(Point2D target)
{
	return (target.x > pos.x && target.x < pos.x + size.x && target.y > pos.y && target.y < pos.y + size.y);
}

//This function checks for a collision against a point/size
bool Box2D::BoxCollision(Point2D target, Size2D targetSize)
{
	return BoxCollision(Box2D(target, targetSize));
}

//This function checks for collision against another Box
bool Box2D::BoxCollision(const Box2D& target)
{
	return (	BoxCollision(target.pos) || BoxCollision(target.pos + target.size.XComponent()) ||
				BoxCollision(target.pos + target.size.YComponent()) || BoxCollision(target.pos + target.size));
}