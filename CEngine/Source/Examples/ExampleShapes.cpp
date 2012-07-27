//This example is about the three main shape classes that CEngine provides- 
//Box2D, Circle2D, and Ray2D.
//These classes should serve well for most needs of positional data in your game,
//as well as anything regarding 2D collisions.
//The main takeaway information for this example is in MainState::Update, where
//various operations using these classes are performed.

//Naturally, you may want to play around with the various position/size values of each of the created shapes
//to fully test them out

#include "Box2D.h"
#include "Circle2D.h"
#include "Ray2D.h"
#include "Collision.h"
#include "ProgramControl.h"
#include "GameState.h"
#include "CEMath.h"
#include <Windows.h>
#include <gl/GL.h>
#include <iostream>

using namespace std;
using namespace CEngine;

//Undefine SDL's main symbol
#undef main

class MainState : public GameState
{
public:
	MainState(StateMachine *_Owner, GameData *_Storage) : GameState(_Owner, _Storage) {}

	void Enter()
	{

	}
	void Update(float deltaTime)
	{
		//The Box2D class has two main constructors... one to take 4 floats and the other, 2 Vector2Ds
		//4 floats are x position, y position, then width and height
		Box2D box1(50, 50, 75, 75);
		//Vector2Ds are naturally position and size respectively
		Box2D box2(Vector2D(50, 150), Vector2D(75, 75));

		//To change these later on just use the public Box2D members 'pos' and 'size'
		box1.pos.y = 90;
		box2.size.x = 25;
		
		//Clear the console to prevent our text constantly flowing.... not the best thing but hey
		system("cls");

		//Collision between boxes is handled with the Overlap function
		if (box1.Overlap(box2)) cout << "Box 1 collides with Box 2" << endl;
		//For a single point, you can also use the Contains function to see if that point is inside the box
		if (box1.Contains(Vector2D(5, 5))) cout << "Box 1 contains supplied point" << endl;
		//The Contains function can also take a Box2D to see if the original box completely contains the other!

		//The Circle2D class has a main constructor that takes a Vector2D and a float
		//Position and radius, respectively
		Circle2D circle1(Vector2D(300, 300), 10);
		Circle2D circle2(Vector2D(350, 300), 75);

		//Of course you can access a circle's 'pos' and 'radius' members directly
		circle1.radius = 20;

		//The Circle2D class also has an Overlap function for other circles
		if (circle1.Overlap(circle2)) cout << "Circle 1 collides with Circle 2" << endl;
		//Plus the Contains function
		if (circle1.Contains(Vector2D(300, 300))) cout << "Circle 1 contains supplied point" << endl;

		//Now, the Ray2D class has a main constructor which takes two Vector2Ds
		//One for the starting point of the ray, and one for the direction of the ray
		//Note that the 'direction' vector also specifies the length of the ray!!!
		Ray2D ray1(Vector2D(0, 0), Vector2D(800, 600));
		Ray2D ray2(Vector2D(50, 500), Vector2D(400, -400));

		//Ray2D's members are also public
		//ray.origin, ray.direction

		//Collision between rays is handled using the IntersectionPoint function
		//This will return the intersection point between the two, or the constant Collision::NoIntersection if there is none
		if (ray1.IntersectionPoint(ray2) != Collision::NoIntersection) cout << "Ray 1 intersects with Ray 2" << endl;
		//There is also the Intersects function to eliminate the need for a comparison
		//e.g. if (ray1.Intersects(ray2))
		//The Ray2D class also has a Contains function for points- this checks if the supplied point lies on our ray
		//It's not expected to be used a lot, but it is used internally for intersection checks
		if (ray1.Contains(Vector2D(800, 600))) cout << "Ray 1 contains specified point" << endl;

		//For collision checks between differing shapes, there is the Collision namespace, which provides various intersection/overlap functions
		//Ray-Box intersection has both an Intersection and Intersects function, like Ray2D
		if (Collision::RayBoxIntersection(ray1, box1) != Collision::NoIntersection) cout << "Ray 1 and Box 1 intersect" << endl;
		//or if (Collision::RayBoxIntersects(ray1, box1)
		//Same goes for Ray-Circle intersection
		if (Collision::RayCircleIntersection(ray1, circle1) != Collision::NoIntersection) cout << "Ray1 and Circle 1 intersect" << endl;
		//or if (Collision::RayCircleIntersects(ray1, circle1)
		//Plus there is an Overlap function for Circles and Boxes
		if (Collision::CircleBoxOverlap(circle1, box1)) cout << "Circle 1 and Box 1 overlap" << endl;

		DrawBox(box1); DrawBox(box2);
		DrawCircle(circle1); DrawCircle(circle2);
		DrawRay(ray1); DrawRay(ray2);
	}
	void Exit()
	{

	}
	State *Clone(StateMachine *NewOwner) const
	{
		return new MainState(NewOwner, GameStorage);
	}
	//Helper functions for drawing!
	void DrawBox(Box2D b)
	{
		glPushMatrix();
		glTranslatef(b.pos.x, b.pos.y, 0.0f);
		glBegin(GL_LINE_LOOP);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(0.0f, b.size.y);
			glVertex2f(b.size.x, b.size.y);
			glVertex2f(b.size.x, 0.0f);
		glEnd();
		glPopMatrix();
	}
	void DrawCircle(Circle2D c)
	{
		glPushMatrix();
		glTranslatef(c.pos.x, c.pos.y, 0.0f);
		glBegin(GL_LINE_LOOP);
			Vector2D p;
			for (float angle = 0.0f; angle < 361.0f; angle++)
			{
				p = Math::AngledVector(angle, c.radius);
				glVertex2f(p.x, p.y);
			}
		glEnd();
		glPopMatrix();
	}
	void DrawRay(Ray2D r)
	{
		glPushMatrix();
		glTranslatef(r.origin.x, r.origin.y, 0.0f);
		glBegin(GL_LINES);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(r.direction.x, r.direction.y);
		glEnd();
		glPopMatrix();
	}

private:
};

int main()
{
	//Set up our graphics window and basic state (see ProgramControl documentation)
	ProgramControl Control("Shapes Example", 800, 600);

	Control.AddState(1, new MainState(&Control, Control.GetGameData()));
	Control.ChangeState(1);

	while (!Control.IsExiting())
	{
		Control.GetWindow()->ClearScreen();

		Control.Update(Control.TimeSinceLastUpdate());

		Control.GetWindow()->UpdateScreen();
	}

	return 0;
}