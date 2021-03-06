/******************************************************************
*CEngine
*InputManager.cpp by Chris Lewis
*Implementation file for the InputManager class
******************************************************************/

#include "Input.h"

using namespace CEngine;

//Default constructor zeros our main variables- the keys array has to be initialised in the body
InputManager::InputManager()
	: leftMouseDown(false), midMouseDown(false), rightMouseDown(false)
{
	for (int i = 0; i < SDLK_LAST; i++) keys[i] = false;
}

//This function checks for input event types and processes them accordingly
bool InputManager::ProcessEvent(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) 
		ProcessKeys(e.key);
	else if (e.type == SDL_MOUSEMOTION)
		ProcessMouseMove(e.motion);
	else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
		ProcessMouseDown(e.button);
	else
		return false;

	return true;
}

//This function returns the status of a specific key
bool InputManager::GetKey(int c) const
{
	if (c < 0 || c >= SDLK_LAST) throw KeyIndexException("Invalid Key Index- Out of Bounds");
	return keys[tolower(c)];
}

//This function returns our mouse position
Vector2D InputManager::GetMousePosition() const
{
	return mousePosition;
}

//This function returns the status of a mouse button
bool InputManager::GetMouseDown(int id) const
{
	if (id == SDL_BUTTON_LEFT) return leftMouseDown;
	else if (id == SDL_BUTTON_MIDDLE) return midMouseDown;
	else if (id == SDL_BUTTON_RIGHT) return rightMouseDown;
	else return false;
}

//This function processes keyboard input
void InputManager::ProcessKeys(SDL_KeyboardEvent e)
{
	if (e.state == SDL_PRESSED) keys[e.keysym.sym] = true;
	else if (e.state == SDL_RELEASED) keys[e.keysym.sym] = false;
}

//This function processes mouse movement input
void InputManager::ProcessMouseMove(SDL_MouseMotionEvent e)
{
	mousePosition.x = e.x;
	mousePosition.y = e.y;
}

//This function processes mouse button input
void InputManager::ProcessMouseDown(SDL_MouseButtonEvent e)
{
	//SDL_PRESSED is 1 and SDL_RELEASED is 0 so can use the button state alone to check for true/false
	if (e.button == SDL_BUTTON_LEFT)
		leftMouseDown = e.state ? true : false;
	else if (e.button == SDL_BUTTON_MIDDLE)
		midMouseDown = e.state ? true : false;
	else if (e.button == SDL_BUTTON_RIGHT)
		rightMouseDown = e.state ? true : false;
}