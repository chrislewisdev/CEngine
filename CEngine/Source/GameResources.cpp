/*******************************************************************
*CEngine
*GameResources.cpp by Chris Lewis
*Implementation of game resources storage
*******************************************************************/

#include "GameResources.h"

using namespace std;
using namespace CEngine;

//Define our static GameResources storage
map<string, ResourcePointer> GameResources::Resources;

//This function adds a new Resource into our storage
void GameResources::AddResource(string name, Resource *newResource)
{
	Resources.insert(pair<string, ResourcePointer>(name, ResourcePointer(newResource)));
}

//This function retrieves a Resource from our storage
Resource *GameResources::GetResource(string name)
{
	ResourceCollection::iterator resource = Resources.find(name);
	if (resource == Resources.end())
	{
		string msg = "Resource not found: " + name;
		throw ResourceNotFoundException(msg.c_str());
	}
	return resource->second.get();
}