/***************************************************************
*CEngine
*GameObjectHandle.cpp by Chris Lewis
***************************************************************/

#include "GameObjectHandle.h"

using namespace CEngine;

//Constructor
GameObjectHandle::GameObjectHandle(GameObjectInstance &inst)
	: reference(inst.instance)
{
	
}

//Bool operator checks to see if our reference is still valid
GameObjectHandle::operator bool()
{
	return !reference.expired();
}

//Declare normal pointer operator
GameObject *GameObjectHandle::operator -> () const
{
	return reference.lock().get();
}