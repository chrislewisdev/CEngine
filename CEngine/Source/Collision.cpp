/****************************************************************
*CEngine
*Collision.cpp by Chris Lewis
****************************************************************/

#include "Collision.h"

namespace CEngine
{
	namespace Collision
	{
		const Vector2D NoIntersection(-1.23456789f, -1.23456789f);

		//This function checks for intersection between Ray2D and Box2D
		Vector2D RayBoxIntersection(const Ray2D& ray, const Box2D& box)
		{
			//Flags for potential intersections on the various sides of the box
			bool minX = true, maxX = true, minY = true, maxY = true;

			//Check for the ray starting INSIDE the box- if so, return the origin as our intersection
			if (box.Contains(ray.origin)) return ray.origin;

			//Begin to rule out sides of intersection based on where our ray starts in relation to the box
			//This means we can check for any side without the chance of detecting an intersection on the FAR side of the box
			if (ray.origin.x < box.pos.x)
			{
				//Ray is to the left of the box- can't be intersecting with the right side (max X)
				maxX = false;
			}
			else if (ray.origin.x >= box.pos.x && ray.origin.x <= box.pos.x + box.size.x)
			{
				//Ray is in the middle X range of the box- can't be intersecting with the left or right side (min/max X)
				minX = false; maxX = false;
			}
			else if (ray.origin.x > box.pos.x + box.size.x)
			{
				//Ray is to the right of the box- can't be intersecting with the left side (min X)
				minX = false;
			}
			if (ray.origin.y < box.pos.y)
			{
				//Ray is above the box- can't be intersecting with the underside (max Y)
				maxY = false;
			}
			else if (ray.origin.y >= box.pos.y && ray.origin.y <= box.pos.y + box.size.y)
			{
				//Ray is in the middle Y range of the box- can't be intersecting with top or bottom (min/max Y)
				minY = false; maxY = false;
			}
			else if (ray.origin.y > box.pos.y + box.size.y)
			{
				//Ray is under the box- can't be intersecting with the top side (min Y)
				minY = false;
			}

			//Now, depending on our valid sides, begin to check for intersection
			//Left side of box
			if (minX)
			{
				float leftSideX = box.pos.x;
				Vector2D i(leftSideX, 0);
				//Get parametric distance in X and apply to Y
				float p = (leftSideX - ray.origin.x) / ray.direction.x;
				i.y = ray.origin.y + p * ray.direction.y;

				//If this is a valid intersection point, return it
				if (box.Contains(i) && p <= 1 && p >= 0) return i;
			}
			//Right side of box
			if (maxX)
			{
				float rightSideX = box.pos.x + box.size.x;
				Vector2D i(rightSideX, 0);
				//Get parametric distance in X and apply to Y
				float p = (rightSideX - ray.origin.x) / ray.direction.x;
				i.y = ray.origin.y + p * ray.direction.y;

				//If this is a valid intersection point, return it
				if (box.Contains(i) && p <= 1 && p >= 0) return i;
			}
			//Top side of box
			if (minY)
			{
				float topSideY = box.pos.y;
				Vector2D i(0, topSideY);
				//Get parametric distance in Y and apply to X
				float p = (topSideY - ray.origin.y) / ray.direction.y;
				i.x = ray.origin.x + p * ray.direction.x;

				//If this is a valid intersection point, return it
				if (box.Contains(i) && p <= 1 && p >= 0) return i;
			}
			//Underside of box
			if (maxY)
			{
				float underSideY = box.pos.y + box.size.y;
				Vector2D i(0, underSideY);
				//Get parametric distance in Y and apply to X
				float p = (underSideY - ray.origin.y) / ray.direction.y;
				i.x = ray.origin.x + p * ray.direction.x;

				//If this is a valid intersection point, return it
				if (box.Contains(i) && p <= 1 && p >= 0) return i;
			}

			//If all our sides failed the check, there is no intersection
			return NoIntersection;
		}

		//This function checks for an intersection between a ray and a circle
		Vector2D RayCircleIntersection(const Ray2D& ray, const Circle2D& circle)
		{
			//Get the unit vector of our direction
			Vector2D d = ray.direction.UnitVector();

			//First check for the ray starting inside the circle
			if (circle.Contains(ray.origin)) return ray.origin;

			//Get the vector from the ray start to the circle center
			Vector2D e = circle.pos - ray.origin;

			float a = e.DotProduct(d);

			float fSquared = circle.radius * circle.radius - e.DotProduct(e) + a * a;

			//If f-squared is negative, there is no intersection
			if (fSquared < 0) return NoIntersection;

			//Solve for t, the parametric distance (through 0..length) along our ray to the intersection point
			float t = a - sqrt(fSquared);

			//Check if this point is valid for both our circle and our ray
			Vector2D i = ray.origin + t * d;
			if (t >= 0 && t < ray.direction.Length())
			{
				return i;
			}
			else 
			{
				return NoIntersection;
			}
		}

		//This function checks for an overlap between a box and a circle
		bool CircleBoxOverlap(const Circle2D& circle, const Box2D& box)
		{
			//Find the closest point on the box to our circle
			Vector2D cp(circle.pos);
			if (cp.x < box.pos.x) cp.x = box.pos.x;
			else if (cp.x > box.pos.x + box.size.x) cp.x = box.pos.x + box.size.x;
			if (cp.y < box.pos.y) cp.y = box.pos.y;
			else if (cp.y > box.pos.y + box.size.y) cp.y = box.pos.y + box.size.y;

			//If the circle contains this point, we have an overlap
			return circle.Contains(cp);
		}
	}
}