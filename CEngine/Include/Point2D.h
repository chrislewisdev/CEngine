/**********************************************
*CEngine
*Point2D.h by Chris Lewis
*Declaration for Point2D struct
*Storage for general 2D positions and sizes
**********************************************/

//Include guard
#ifndef CENGINE_POINT2D_H
#define CENGINE_POINT2D_H

//Declare struct in the CEngine namespace
namespace CEngine
{
	//Declare all functions inlined since this is a pretty basic struct
	struct POINT2D
	{
		//Default constructor
		POINT2D() : x(0), y(0){}
		//Constructor to initialise both values
		POINT2D(float X, float Y) : x(X), y(Y){}

		//Declare co-ordinate properties
		float x, y;

		//Declare operators
		friend POINT2D operator +(POINT2D& lhs, POINT2D& rhs)
			{return POINT2D(lhs.x + rhs.x, lhs.y + rhs.y);}
		friend POINT2D operator -(POINT2D& lhs, POINT2D& rhs)
			{return POINT2D(lhs.x - rhs.x, lhs.y - rhs.y);}
	};

	//Declare a size alias for points
	typedef POINT2D SIZE2D;
}

#endif