/*******************************************************************
*CEngine
*GameObjectInstance.h by Chris Lewis
*Class to wrap game object pointers with a numeric ID (so that entries can be sorted)
*******************************************************************/

#ifndef GAMEOBJECTINSTANCE_H
#define GAMEOBJECTINSTANCE_H

#include <boost/shared_ptr.hpp>

namespace CEngine
{
	/// \class CEngine::GameObjectPointer
	/// \brief Alias for boost::shared_ptr<GameObject>, used by GameData class for GameObject pointers
	typedef boost::shared_ptr<GameObject> GameObjectPointer;

	//Structure: GameObject <- Shared Pointer <- GameObjectInstance <- GameObjectHandle
	/// \brief GameObjectInstance is a wrapper class for GameObjectPointers that associates an ID with each pointer.
	///
	/// Instances of the class can then be sorted by this ID leading to faster item retrieval in collections.
	/// Provides the -> operator so that it can be used just like any smart pointer.
	class GameObjectInstance
	{
	public:
		//! Main Constructor, initialises pointer to a GameObject and takes a unique ID
		GameObjectInstance(GameObject *o)
			: instance(o), id(creationCounter++)
		{

		}

		//! -> operator to retrieve our GameObject like with any regular pointer
		GameObject* operator -> ()
		{
			return instance.get();
		}
		//! Const version of the -> operator for read-only usage of GameObjectInstance
		const GameObject* operator -> () const
		{
			return instance.get();
		}
		//! Comparison operator so this class can be sorted in collections
		bool operator < (const GameObjectInstance& other)
		{
			return (id < other.id);
		}

	private:
		//Declare private properties
		//! Shared Pointer to our particular GameObject instance
		GameObjectPointer instance;
		//! Our numeric ID for sorting
		unsigned int id;
		//! Static counter for creation of new IDs for each instance
		static unsigned int creationCounter;
	};
}

#endif