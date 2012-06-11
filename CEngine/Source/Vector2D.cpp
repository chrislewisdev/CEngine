/*****************************************************************
*CEngine
*Vector2D.cpp by Chris Lewis
*Implementation file for the Vector2D class
*****************************************************************/

#include <cmath>
#include "Vector2D.h"

using namespace CEngine;

//Define our Default Constructor
Vector2D::Vector2D()
	: x(0), y(0)
{

}

//Define our initialisation constructor
Vector2D::Vector2D(float _x, float _y)
	: x(_x), y(_y)
{

}

//This function returns the length of our vector
float Vector2D::Length() const
{
	return sqrt(x*x + y*y);
}

//This function returns a unit-vector in the same direction as our vector
Vector2D Vector2D::UnitVector() const
{
	float length = Length();
	if (length == 0) throw std::invalid_argument("Attempted to create Unit Vector on a Zero Vector");
	return Vector2D(x/length, y/length);
}

//This function calculates the dot product of this vector with another
float Vector2D::DotProduct(const Vector2D& target) const
{
	return (x * target.x + y * target.y);
}

//This function returns the X Component of this vector
Vector2D Vector2D::XComponent() const
{
	return Vector2D(x, 0);
}

//This function returns the Y Component of this vector
Vector2D Vector2D::YComponent() const
{
	return Vector2D(0, y);
}

//Vector += operator
Vector2D& Vector2D::operator += (const Vector2D& rhs)
{
	this->x += rhs.x; this->y += rhs.y;
	return *this;
}

//Vector -= operator
Vector2D& Vector2D::operator -= (const Vector2D& rhs)
{
	this->x -= rhs.x; this->y -= rhs.y;
	return *this;
}

//Vector *=
Vector2D& Vector2D::operator *= (float rhs)
{
	this->x *= rhs; this->y *= rhs;
	return *this;
}

//Vector division
Vector2D Vector2D::operator / (float rhs)
{
	if (rhs == 0) throw std::invalid_argument("Vector / attempted to divide by zero.");
	return Vector2D(this->x / rhs, this->y / rhs);
}

//Vector /=
Vector2D& Vector2D::operator /= (float rhs)
{
	if (rhs == 0) throw std::invalid_argument("Vector /= attempted to divide by zero.");
	this->x /= rhs; this->y /= rhs;
	return *this;
}

//Vector negation operator
Vector2D Vector2D::operator - () const
{
	return Vector2D(-x, -y);
}