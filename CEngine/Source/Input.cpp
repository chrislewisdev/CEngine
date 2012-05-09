/******************************************************************
*CEngine
*Input.cpp by Chris Lewis
*Implementation file for the Input class
******************************************************************/

#include "Input.h"

using namespace CEngine;

//Default constructor zeros our main variables- the keys array has to be initialised in the body
Input::Input()
	: leftMouseDown(false), midMouseDown(false), rightMouseDown(false)
{
	for (int i = 0; i < SDLK_LAST; i++) keys[i] = false;
}