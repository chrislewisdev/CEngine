/************************************************************
*CEngine
*GameObjectInstance.cpp by Chris Lewis
************************************************************/

#include "GameObjectInstance.h"

using namespace CEngine;

//Constructor initialise our shared pointer instance and ID
GameObjectInstance::GameObjectInstance(GameObject *o)
	: instance(o), id(creationCounter++)
{

}

GameObjectInstance::GameObjectInstance(const GameObjectInstance& other)
	: instance(other.instance), id(creationCounter++)
{

}

//-> operator for pointer-like behaviour
GameObject *GameObjectInstance::operator -> () const
{
	return instance.get();
}