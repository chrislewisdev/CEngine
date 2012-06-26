/*********************************************************************
*CEngine
*Ray2D.h by Chris Lewis
*Defines a basic implementation of Rays for raycasting and other operations
*********************************************************************/

#ifndef CENGINE_RAY2D_H
#define CENGINE_RAY2D_H

#include "Vector2D.h"

namespace CEngine
{
	/// \brief Used for Raycasting and related space/collision data.
	///
	/// The Ray2D class is a relatively simple implementation of Rays using Vectors to represent its Origin and Direction. This is primarily
	/// designed to be used in collisions against other shapes like AABBs (the Box2D class) and, of course, other Rays.
	class Ray2D
	{
	public:
		//! Main Constructor. Must initialise both origin and direction of Ray.
		Ray2D(Vector2D o, Vector2D d);

		//Declare public properties
		//! Vector dictating our origin position
		Vector2D origin;
		//! Vector dictating our Ray direction
		Vector2D direction;
	};
}

#endif