#include <iostream>
#include "Vector2D.h"

using namespace std;
using namespace CEngine;

int main()
{
	//The Vector2D class serves as the primary class for anything regarding x/y co-ordinates.
	//If you aren't familiar with vectors I suggest you read about them, but in the most basic sense
	//you can think of these as just a pair of x/y values, like in any co-ordinate system.

	//The default Vector2D constructor sets the x/y values to 0.
	Vector2D zero;
	cout << "X/Y values of default vector: " << zero.x << "," << zero.y << endl;
	//Plus a constructor is provided to set whatever values you want, naturally
	Vector2D set(3, 4);
	cout << "X/Y values of set vector: " << set.x << "," << set.y << endl;
	
	//All the typical operations of a vector are provided: most importantly, addition/subtraction and so on
	Vector2D a(1, 5);
	Vector2D add = zero + set + a;
	Vector2D minus = set - a;
	cout << "X/Y values after addition: " << add.x << "," << add.y << endl;
	cout << "X/Y values after subtraction: " << minus.x << "," << minus.y << endl;
	//Multiplying a vector by a single value is the same as multiplying its x/y values by that value
	Vector2D multiplication = a * 2;
	//And same for division
	Vector2D division = a / 2;
	cout << "X/Y values after multiplication: " << multiplication.x << "," << multiplication.y << endl;
	cout << "X/Y values after division: " << division.x << "," << division.y << endl;
	//The class also supports (in)equality checks as well as vector negation

	//The class supports all common features of a vector, namely....
	//Length
	cout << "Length of vector A is: " << a.Length() << endl;
	//Unit Vector- a vector in the same direction as the original, but with a length of 1
	Vector2D unit = a.UnitVector();
	cout << "X/Y values of unit vector: " << unit.x << "," << unit.y << endl;
	//While not a 'standard' vector operation, the PerpendicularVector function returns a vector of the same length as
	//the original but in a direction perpendicular to the original.
	Vector2D perpendicular = a.PerpendicularVector();
	cout << "X/Y values of perpendicular vector: " << perpendicular.x << "," << perpendicular.y << endl;
	//Dot Products
	cout << "Dot Product of A with its Perpendicular Vector is: " << a.DotProduct(perpendicular) << endl;
	//Also a non-standard operation, the X/YComponent functions return a Vector2D containing only the X/Y value of
	//the original (the other value will be 0)
	Vector2D xOnly = a.XComponent();
	cout << "X/Y values of X Component are: " << xOnly.x << "," << xOnly.y << endl;

	cin.get();

	return 0;
}