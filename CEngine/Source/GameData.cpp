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
	: SubclassEnforcer(NULL)
{
	
}

//Copy Constructor
GameData::GameData(const GameData& target)
{
	//Check that the target has no objects waiting to be removed
	if (target.RemoveList.size() != 0) throw CopyException("Attempted to copy a GameData instance that has objects waiting to be removed.");
	Copy(target);
}

//Assignment operator
const GameData& GameData::operator = (const GameData& target)
{
	//Check that the target has no objects waiting to be removed
	if (target.RemoveList.size() != 0) throw CopyException("Attempted to copy a GameData instance that has objects waiting to be removed.");

	//Clear out our own data
	ClearAll();

	Copy(target);

	return *this;
}

//Destructor will explicitly clear out our existing game data
GameData::~GameData()
{
	ClearAll();
}

//This function adds a new GameObject waiting to be added into the gamestate
void GameData::AddObject(GameObject *object)
{
	CheckSubclass(object);
	AddList.push_back(GameObjectPointer(object));
}

//This function adds a new GameObject and returns a Handle referencing it
GameObjectHandle GameData::AddObjectWithHandle(GameObject *object)
{
	CheckSubclass(object);
	GameObjectPointer add(object);
	GameObjectHandle handle(add);
	AddList.push_back(add);
	return handle;
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
	//Run through our current list to make sure this target hasn't already been added
	for (vector<GameObjectCollection::iterator>::iterator cdtr = RemoveList.begin(); cdtr != RemoveList.end(); cdtr++)
	{
		if (*cdtr == target) return;
	}
	RemoveList.push_back(target);
}

//This function requests that a range of objects be removed from the game state
void GameData::RemoveObject(GameObjectCollection::iterator begin, GameObjectCollection::iterator end)
{
	for (GameObjectCollection::iterator cdtr = begin; cdtr != end; cdtr++)
	{
		RemoveObject(cdtr);
	}
}

//This function removes all currently waiting objects from the game
void GameData::PerformBatchRemove()
{
	for (vector<GameObjectCollection::iterator>::iterator cdtr = RemoveList.begin(); cdtr != RemoveList.end(); cdtr++)
	{
		if (!(*cdtr)->unique()) throw DanglingPointerException("Attempted to delete GameObject with other existing shared_ptr references");
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
int GameData::ObjectCount() const
{
	return Objects.size();
}

//This function copies data from another GameData instance
void GameData::Copy(const GameData& target)
{
	//Copy the Add List from the target
	for (vector<GameObjectPointer>::const_iterator cdtr = target.AddList.begin(); cdtr != target.AddList.end(); cdtr++)
	{
		AddObject((*cdtr)->Clone());
	}
	//Copy the core Objects list
	for (GameObjectCollection::const_iterator cdtr = target.Objects.begin(); cdtr != target.Objects.end(); cdtr++)
	{
		Objects.push_back(GameObjectPointer((*cdtr)->Clone()));
	}
}

//This function clears all our data lists
void GameData::ClearAll()
{
	AddList.clear();
	Objects.clear();
	RemoveList.clear();
}

//This function sets our current subclass enforcement to the specified type
template <class T> void GameData::EnforceSubclass()
{
	//Check that the specified type is a valid subclass of GameObject at all
	try
	{
		GameObject check;
		dynamic_cast<T*>(&check);
	}
	catch (bad_cast& e)
	{
		throw InvalidSubclassException("Type specified for subclass enforcement not a child of GameObject!");
	}
	SubclassEnforcer = CheckSubclass<T>;
}

//This function stops us from enforcing any subclass
void GameData::StopEnforcingSubclass()
{
	SubclassEnforcer = NULL;
}

//This function checks the passed GameObject against our current subclass enforcer
void GameData::CheckSubclass(GameObject *object)
{
	if (SubclassEnforcer && !SubclassEnforcer(object))
	{
		string error = "GameObject passed to AddObject violated subclass enforcement. Type was ";
		error += string(typeid(object).name());
		throw InvalidSubclassException(error.c_str());
	}
}