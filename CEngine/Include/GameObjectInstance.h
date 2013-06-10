/*******************************************************************
*CEngine
*GameObjectInstance.h by Chris Lewis
*Class to wrap game object pointers with a numeric ID (so that entries can be sorted)
*******************************************************************/

#ifndef GAMEOBJECTINSTANCE_H
#define GAMEOBJECTINSTANCE_H

#include "GameObject.h"
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
		GameObjectInstance(GameObject *o);
		GameObjectInstance(const GameObjectInstance& other);

		//! -> operator to retrieve our GameObject like with any regular pointer
		GameObject *operator -> () const;
		//! * operator to retrieve the raw GameObject pointer (not be used lightly!)
		GameObject *operator * () const;
		//! Give < operator friend access for comparisons
		friend bool operator < (const GameObjectInstance& left, const GameObjectInstance& right)
		{
			return (left.id < right.id);
		}

	private:
		//Disable copy construction and copy operations by declaring them private

		//Declare private properties
		//! Shared Pointer to our particular GameObject instance
		GameObjectPointer instance;
		//! Our numeric ID for sorting
		const unsigned int id;
		//! Static counter for creation of new IDs for each instance
		static unsigned int creationCounter;

		//Declare GameObjectHandle a friend so it can directly access our pointer instance (for implementing the -> operator more easily)
		friend class GameObjectHandle;
		friend class GameData;
	};

	//! Comparison operator so this class can be sorted in collections
	//bool operator < (const GameObjectInstance& left, const GameObjectInstance right)
	
}

#endif