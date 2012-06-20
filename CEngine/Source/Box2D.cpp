/******************************************************************
*CEngine
*Box2D.cpp by Chris Lewis
*Implementation file of Box2D struct
******************************************************************/

//Include necessary headers
#include "Box2D.h"
#include "CEMath.h"

using namespace CEngine;

//Define our default constructor
Box2D::Box2D()
{

}

//Constructor to take position/size
Box2D::Box2D(Vector2D p, Vector2D s)
	: pos(p), size(s)
{

}

//Constructor to take individual position/size values
Box2D::Box2D(float x, float y, float xSize, float ySize)
	: pos(x, y), size(xSize, ySize)
{

}

//This function checks for a point collision inside our box
bool Box2D::Contains(Vector2D target) const
{
	return (target.x >= pos.x && target.x <= pos.x + size.x && target.y >= pos.y && target.y <= pos.y + size.y);
}

//This function checks if the target box is entirely within this one
bool Box2D::Contains(const Box2D& target) const
{
	//For the target box to be contained within us, the target box's bounds must each be the max/min of our intersection area
	if (Math::Max(pos.x, target.pos.x) != target.pos.x) return false;
	if (Math::Min(pos.x + size.x, target.pos.x + target.size.x) != target.pos.x + target.size.x) return false;
	if (Math::Max(pos.y, target.pos.y) != target.pos.y) return false;
	if (Math::Min(pos.y + size.y, target.pos.y + target.size.y) != target.pos.y + target.size.y) return false;

	return true;
}

//This function checks for a collision against a point/size
bool Box2D::Overlap(Vector2D target, Vector2D targetSize) const
{
	return Overlap(Box2D(target, targetSize));
}

//This function checks for collision against another Box
bool Box2D::Overlap(const Box2D& target) const
{
	//Declare storage for our intersection range
	Vector2D intersection;

	//Calculate the intersection widths between us and our target
	intersection.x = Math::Min(pos.x + size.x, target.pos.x + target.size.x) - Math::Max(pos.x, target.pos.x);
	intersection.y = Math::Min(pos.y + size.y, target.pos.y + target.size.y) - Math::Max(pos.y, target.pos.y);

	//If both values are positive, we have a valid area which means we're intersecting
	return (intersection.x > 0 && intersection.y > 0);
}