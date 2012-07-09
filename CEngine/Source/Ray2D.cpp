/*******************************************************************
*CEngine
*Ray2D.cpp by Chris Lewis
*Implementation of Ray2D methods
*******************************************************************/

#include "Ray2D.h"
#include "Collision.h"

using namespace CEngine;

//Main Constructor
Ray2D::Ray2D(Vector2D o, Vector2D d)
	: origin(o), direction(d)
{

}

//This function checks if the target point lies on our ray
bool Ray2D::Contains(const Vector2D& target) const
{
	//Get the normal to our line
	Vector2D n = direction.PerpendicularVector().UnitVector();

	//Check if this point satisfies our line equation
	if (abs(n.DotProduct(origin) - n.DotProduct(target)) > 0.01f)
	{
		return false;
	}

	//Check that it's within the range of our actual ray
	Vector2D toTarget = target - origin;
	if (toTarget.Length() > direction.Length() || toTarget.DotProduct(direction) < 0)
	{
		return false;
	}

	return true;
}

//This function checks for intersection against another Ray
Vector2D Ray2D::IntersectionPoint(const Ray2D& target) const
{
	//Get the normal to our line and theirs
	Vector2D n1 = direction.PerpendicularVector().UnitVector();
	Vector2D n2 = target.direction.PerpendicularVector().UnitVector();

	//Check for either of our rays containing the start-/end-point of the other
	//In these cases, the returned point may essentially depend on the precedence of these if statements
	//This could perhaps be considered undesirable, but in the case of overlapping rays, there may be many points of intersection of which
	//you can't really choose a 'right' one
	if (Contains(target.origin)) return target.origin;
	if (Contains(target.origin + target.direction)) return target.origin + target.direction;
	if (target.Contains(origin)) return origin;
	if (target.Contains(origin + direction)) return origin + direction;

	//Check for parallel normals (indicates we can't be intersecting)
	//Even though n1 == -n2 is likely to indicate opposite rays, they still count as the same line and would entail an incorrect calculation of i
	if (n1 == n2 || n1 == -n2)
	{
		return Collision::NoIntersection;
	}

	//Calculate the point of intersection between the two rays (not considering ray bounds just yet)
	//The following math is all primarily derived from i.n1 == p.n1 && i.n2 == q.n2
	//Where: i = point of intersection, p = origin of ray 1, n1 = normal to the line of ray 1,
	//And:	 q = origin of ray 2, n2 = normal to the line of ray 2
	Vector2D i;
	float pDotN = target.origin.DotProduct(n2), qDotN = origin.DotProduct(n1);
	//We need special-case code when n1.x == 0 since it is used for division in our equation
	if (n1.x != 0)
	{
		i.y = (pDotN - (n2.x * qDotN) / n1.x) / (n2.y - (n2.x * n1.y) / n1.x);
		i.x = (qDotN - i.y * n1.y) / n1.x;
	}
	else
	{
		//If this ray is a flat horizontal line, we use the parametric y distance from the target to help find our x point
		i.y = origin.y;
		Vector2D d = target.direction.UnitVector();
		float qpY = (i.y - target.origin.y) / d.y;
		i.x = target.origin.x + d.x * qpY;
	}

	//Check that the projected intersection is actually within both our rays
	if (!Contains(i) || !target.Contains(i))
	{
		return Collision::NoIntersection;
	}

	//If all our tests passed, return the intersection point
	return i;
}

//This function checks if our two rays intersect without returning the intersection point
bool Ray2D::Intersects(const Ray2D& target) const
{
	return (IntersectionPoint(target) != Collision::NoIntersection);
}