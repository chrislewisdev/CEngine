/**********************************************
*CEngine
*Point2D.h by Chris Lewis
*Declaration for Point2D struct
*Storage for general 2D positions and sizes
**********************************************/

//Include guard
#ifndef CENGINE_Point2D_H
#define CENGINE_Point2D_H

//Declare struct in the CEngine namespace
namespace CEngine
{
	//Declare all functions inlined since this is a pretty basic struct
	/// \brief Structure for containing basic on-screen co-ordinate data.
	///
	/// Provides simple, public x/y storage along with corresponding Constructors and operator definitions.
	struct Point2D
	{
		//! Default Constructor. Initialises both x/y to 0.
		Point2D() : x(0), y(0){}
		//! Constructor to initialise x/y to the corresponding parameters.
		Point2D(float X, float Y) : x(X), y(Y){}

		//Declare public functions
		/// \brief Returns a Point2D object containing only the X value of this
		/// \return A Point2D object with values (x, 0)
		Point2D XComponent() const {return Point2D(x, 0);}
		/// \brief Returns a Point2D object containing only the Y value of this
		/// \return A Point2D object with values (0, y)
		Point2D YComponent() const {return Point2D(0, y);}

		//Declare co-ordinate properties
		float x, y;

		//Declare operators
		friend Point2D operator +(const Point2D& lhs, const Point2D& rhs)
			{return Point2D(lhs.x + rhs.x, lhs.y + rhs.y);}
		friend Point2D operator -(const Point2D& lhs, const Point2D& rhs)
			{return Point2D(lhs.x - rhs.x, lhs.y - rhs.y);}
	};

	//Declare a size alias for points
	/// \class CEngine::Size2D
	///	\brief Alias for Point2D to be used for size values (e.g implying width/height instead of position).
	typedef Point2D Size2D;
}

#endif