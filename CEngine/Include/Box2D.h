/**********************************************************
*CEngine
*Box2D.h by Chris Lewis
*Declaration for Box2D struct
*Stores point/size data and processes square collisions
**********************************************************/

#ifndef CENGINE_BOX2D_H
#define CENGINE_BOX2D_H

//Include necessary headers
#include "Point2D.h"

//Declare class inside the CEngine namespace
namespace CEngine
{
	/// \brief Structure for containing 2D rectangle data- position/size as well as collision calculations.
	///
	/// All-public class with position ('pos') and size ('size) members, along with overloaded constructors for initialisation.
	/// This class also contains methods to test for Box Collisions with Points and other Boxes
	struct BOX2D
	{
		//! Default constructor, will initialise position/size to (0,0) each
		BOX2D();
		//! Constructor to take explicit position/size structs for initialisation
		BOX2D(POINT2D p, SIZE2D s);
		//! Constructor to take individual float values for position then size
		BOX2D(float x, float y, float xSize, float ySize);

		//Declare public functions
		/// \brief Checks for collision with a single Point- i.e. if the target Point is within our Box
		///
		/// \param target The target position to check against
		/// \return True if there's a collision, false if not
		bool BoxCollision(POINT2D target);
		/// \brief Checks for collision against a Point with a size- if the target area overlaps with our Box
		///
		/// \param target The target position to check against
		/// \param targetSize The width/height values of the target area
		/// \return True if there's a collision, false if not
		bool BoxCollision(POINT2D target, SIZE2D targetSize);
		/// \brief Checks for collision against another Box- if the two Boxes overlap at all
		///
		/// \param target The target Box to check against
		/// \return True if there's a collision, false if not
		bool BoxCollision(BOX2D target);

		//Declare public properties
		//! Position (x,y) struct
		POINT2D pos;
		//! Size (x,y) struct
		SIZE2D size;
	};
}

#endif