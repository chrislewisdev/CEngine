/****************************************************************
*CEngine
*GameData.cpp by Chris Lewis
*Implementation for GameData class to handle game-state storage
****************************************************************/

#include "GameData.h"

using namespace CEngine;
using namespace std;

//Define our constructor- currently no initialisation necessary
GameData::GameData()
{
	
}

//Destructor will explicitly clear out our existing game data
GameData::~GameData()
{
	AddList.clear();
	Objects.clear();
	RemoveList.clear();
}

//This function adds a new GameObject waiting to be added into the gamestate
void GameData::AddObject(GameObjectPointer object)
{
	AddList.push_back(object);
}

//This function adds all currently waiting objects into the game
void GameData::PerformBatchAdd()
{
	for (vector<GameObjectPointer>::iterator cdtr = AddList.begin(); cdtr != AddList.end(); cdtr++)
	{
		Objects.push_back(*cdtr);
	}
	AddList.clear();
}

//This function adds a new GameObject reference waiting to be removed
void GameData::RemoveObject(GameObjectCollection::iterator target)
{
	RemoveList.push_back(target);
}

//This function removes all currently waiting objects from the game
void GameData::PerformBatchRemove()
{
	for (vector<GameObjectCollection::iterator>::iterator cdtr = RemoveList.begin(); cdtr != RemoveList.end(); cdtr++)
	{
		Objects.erase(*cdtr);
	}
	RemoveList.clear();
}

//This function returns our starting iterator for GameObject storage
GameObjectCollection::iterator GameData::Begin()
{
	return Objects.begin();
}

//This function returns our end iterator for GameObject storage
GameObjectCollection::iterator GameData::End()
{
	return Objects.end();
}

//This function returns the size of our collection
int GameData::NumObjects()
{
	return Objects.size();
}