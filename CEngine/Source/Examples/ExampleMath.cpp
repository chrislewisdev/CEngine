//CEMath.h contains a number of miscellaneous math functions housed in the CEngine::Math namespace
#include "CEMath.h"
#include <iostream>

using namespace std;
using namespace CEngine;

int main()
{
	//The following code will demonstrate all existing Math functions in order

	//The Min function provided is a template function that will return the minimum of whatever is passed as its two arguments.
	//Whatever types you pass must be suitable for comparison with the < operator, naturally
	cout << "The minimum of 4 and 10 is: " << Math::Min(4, 10) << endl;
	cout << "The minimum of 4.5 and 10.5 is:" << Math::Min(4.5, 10.5) << endl;
	//The Max function is the same, but returns the maximum number of course
	//Note that the Max function does not require the > operator to be defined- it uses < just like Min
	cout << "The maximum of 1 and 555 is: " << Math::Max(1, 555) << endl;

	//The Angle function returns the Angle in degrees between two vectors- that is, the angle from A to B
	//Note that the range of values returned will always be between (-180, 180].
	//Where the angles will be organised as such:
	//      90
	// 135  |  45
	//    \ | /
	//     \|/
	//180 --O-- 0
	//     /|\
	//    / | \
	//-135  | -45
	//     -90
	//So remember that a return of 0 degrees means that B is to the right of A.

	cout << "The angle where B is directly above A is: " << Math::Angle(Vector2D(0, 0), Vector2D(0, 1)) << endl;
	cout << "The angle where B is directly right of A is: " << Math::Angle(Vector2D(0, 0), Vector2D(1, 0)) << endl;
	cout << "The angle where B is directly left of A is: " << Math::Angle(Vector2D(0, 0), Vector2D(-1, 0)) << endl;
	cout << "The angle where B is directly below A is: " << Math::Angle(Vector2D(0, 0), Vector2D(0, -1)) << endl;

	//The AngledVector function returns a vector pointing at the specified angle (in degrees), with the specified length.
	//Useful for easily creating an angled offset from a point, and combines with the Angle function nicely
	Vector2D angle45 = Math::AngledVector(45, 1);
	cout << "The X/Y values of a vector angled at 45 degrees are: " << angle45.x << "," << angle45.y << endl;

	cin.get();

	return 0;
}