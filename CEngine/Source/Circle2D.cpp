/*****************************************************************
*CEngine
*Circle2D.cpp by Chris Lewis
*****************************************************************/

#include "Circle2D.h"

using namespace CEngine;

//Default constructor initialises everything to 0
Circle2D::Circle2D()
{

}

//Constructor to initialise position/radius values
Circle2D::Circle2D(Vector2D p, float r)
	: pos(p), radius(r)
{

}

//This function checks if the target point is within our circle
bool Circle2D::Contains(Vector2D target) const
{
	return ((target - pos).Length() < radius);
}

//This function checks if the target circle overlaps with this one
bool Circle2D::Overlap(const Circle2D& target) const
{
	return ((target.pos - pos).Length() < radius + target.radius);
}