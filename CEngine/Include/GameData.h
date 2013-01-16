/*****************************************************************
*CEngine
*GameData.h by Chris Lewis
*Declares Game Data class for handling storage of all game objects, level data etc.
*****************************************************************/

#ifndef CENGINE_GAMEDATA_H
#define CENGINE_GAMEDATA_H

#include <list>
#include <vector>
#include <map>
#include <set>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include "GameObject.h"
#include "GameObjectInstance.h"
#include <string>

namespace CEngine
{
	/// \class CEngine::GameObjectHandle
	/// \brief Alias for boost::weak_ptr<GameObject>- use this to reference GameObjects held by GameData from other classes in a 
	/// more persistent manner. Be very careful though not to keep any new shared locks on the object.
	typedef boost::weak_ptr<GameObject> GameObjectHandle;
	/// \class CEngine::GameObjectCollection
	/// \brief Alias for the internal collection used to store GameObjects. Can be used to get the right iterator type for GameObjects.
	typedef std::set<GameObjectInstance> GameObjectCollection;

	//This function checks that the provided GameObject is a valid instance of subclass T
	template <class T> static bool TestSubclass(GameObject *o)
	{
		try
		{
			dynamic_cast<T*>(o);
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	/// \brief Class to hold all active game state data, e.g. managing instances of game objects, current level data, etc.
	///
	/// The GameData class acts as storage for all main data related to the current game-state, like storing all active game objects
	/// in the game, data on the current level and so on. It will also house when appropriate other information designed to work on the
	/// game-state, such as BSP-trees for collision. It is designed to be interfaced with by Game States (and others) to work on the current
	/// game state.
	///
	/// It provides Begin() and End() functions to use for iterating through GameObjects without needing access to the collections themselves.
	/// The GameObjectHandle typedef is provided to use as references to specific GameObjects from classes other than GameData (e.g. other
	/// GameObjects). However take care when using these not to keep any new shared locks on the object- if you do so, when you attempt to
	/// delete the referenced GameObject the GameData class will recognise that there are other references to it and throw a DanglingPointerException.
	/// 
	/// GameData also supports the use of different 'contexts' throughout its lifetime. This allows you store multiple distinct sets of objects in the
	/// same GameData instance without them interfering with each other (e.g. objects for two different game states). Contexts are identified
	/// by names and selected using the SetContext function. The default context upon startup is simply identified by the empty string.
	class GameData
	{
	public:
		//! Default Constructor, creates empty game data
		GameData();
		/// \brief Copy Constructor. Will perform a deep copy of all GameObjects in the other GameData instance as well as all
		/// GameObjects that are waiting to be added. However copying of those waiting to be removed is not possible and as
		/// such this constructor imposes the restriction that the list of objects waiting to be removed on the other GameData instance
		/// MUST be empty prior to copying.
		GameData(const GameData& target);
		/// \brief Assignment Operator. Works just like the Copy Constructor but clears out any existing data before copying.
		const GameData& operator = (const GameData& target);
		//! Destructor. Makes sure all existing game data is cleaned up.
		~GameData();

		//Declare exception classes
		/// \brief Exception class for errors when copying data from one GameData instance to another. Currently only includes
		/// attempting to copy when objects are present in the Removal List.
		class CopyException : public std::exception
		{
		public:
			CopyException(const char *what) : std::exception(what) {}
		};
		/// \brief Exception class for when a dangling shared pointer is detected whilst deleting a GameObject.
		/// It is illegal to keep a shared pointer to a GameObject beyond its lifetime in GameData.
		class DanglingPointerException : public std::exception
		{
		public:
			DanglingPointerException(const char *what) : std::exception(what) {}
		};
		/// \brief Exception class for when a GameObject attempting to be added to our GameData violates the subclass requirement
		/// set with GameData::EnforceSubclass().
		class InvalidSubclassException : public std::exception
		{
		public:
			InvalidSubclassException(const char *what) : std::exception(what) {}
		};

		//Declare public functions
		/// \brief Sets the current storage context to that of the specified ID. If the specified context does not exist, it will be
		/// created. Note that any pending object additions/removals will be performed before the context is changed.
		///
		/// \param id A string indicating the context to switch to.
		/// \return void
		void SetContext(const std::string& id);
		/// \brief Requests a new object be added to the game state. Note that the new object will not be actually added into the proper
		/// game state until a Batch Add is performed (at the start of a new program Update)
		///
		/// \param object A (most likely new'd) pointer to the object to add in.
		/// \return void
		void AddObject(GameObject *object);
		/// \brief Same as AddObject, but returns a GameObjectHandle referencing the object you provided. Use this to access the new object
		/// as you see fit, but remember that the object itself will still not be part of the current game scene until a batch add is
		/// performed. Use with care!
		///
		/// \param object A (most likely new'd) pointer to the object to add in.
		/// \return A GameObjectHandle referencing the object you just added.
		GameObjectHandle AddObjectWithHandle(GameObject *object);
		/// \brief Performs a batch add of objects into the game state, putting all requested new objects into our actual object collection.
		/// \return void
		void PerformBatchAdd();
		/// \brief Requests that an object referenced by the specified iterator be removed from the game state. Note that will not actually
		/// be removed until a Batch Remove is performed (at the end of a new program Update). Also checks to see that the target
		/// iterator has not already been requested to remove.
		///
		/// \param target The GameObject Collection iterator referencing the object to be removed.
		/// \return void
		void RemoveObject(GameObjectCollection::iterator target);
		/// \brief Requests that a range of iterators be removed from the game state (largely the same as the first RemoveObject).
		///
		/// \param begin Iterator indicating the start of a range of objects to remove.
		/// \param end End iterator which specifies where to stop removing (will NOT remove the end iterator itself)
		/// \return void
		void RemoveObject(GameObjectCollection::iterator begin, GameObjectCollection::iterator end);
		/// \brief Performs a batch remove of all objects currently waiting to be removed from the game state
		/// \return void
		void PerformBatchRemove();
		/// \brief Clears out all data in the current context. This includes all current Game Objects plus any that are waiting to be added,
		/// and naturally cancels out all pending removals. Useful as a flatout reset for your game data where appropriate. Just make sure you
		/// have no hanging references afterwards!
		/// \return void
		void ClearCurrentContext();
		/// \brief Same as ClearCurrentContext, but clears out data for ALL Object Contexts, and goes back to the default context. 
		/// Good for a complete reset of your game data.
		/// \return void
		void ClearAll();
		/// \brief Returns the starting iterator for our collection of GameObjects.
		/// \return An iterator referencing the start of our GameObjects collection.
		GameObjectCollection::iterator Begin();
		/// \brief Returns the end iterator for our collection of GameObjects.
		/// \return An iterator signifying the last element in our collection.
		GameObjectCollection::iterator End();
		/// \brief Returns the no. of GameObjects currently in our collection
		/// \return An integer representing our collection size.
		int ObjectCount() const;
		/// \brief Stops GameData from checking added GameObjects against any previously specified subclass.
		/// \return void.
		void StopEnforcingSubclass();
		/// \brief Template function to make GameData begin enforcing that all added objects are instances of the specified subclass
		/// of GameObject. Useful if you want to introduce your own master subclass of GameObject from which all your GameObjects
		/// inherit, and make sure this is never violated. Note that if you set the type as a non-subclass of GameObject, all future
		/// Add calls will fail until you fix it!
		/// \return void
		template <class T> void EnforceSubclass()
		{
			SubclassEnforcer = TestSubclass<T>;
		}

	private:
		//Declare private functions
		//! Copies data from another GameData. Used in Copy Constructor and operator =
		void Copy(const GameData &target);
		//! Checks the passed GameObject against our current subclass enforcer.
		void CheckSubclass(GameObject *object);

		//Declare private properties
		//Collection of GameObjectPointers to add into our collection on the next batch add
		std::vector<GameObjectPointer> AddList;
		//Map of all our different Object Contexts
		std::map< std::string, GameObjectCollection > ObjectContexts;
		//Collection of all game objects currently in our game state
		GameObjectCollection *Objects;
		//Collection of iterators referencing objects to be removed in our next batch remove
		std::vector<GameObjectCollection::iterator> RemoveList;
		//Function pointer to our suitable 'check subclass' function for GameObjects
		bool (*SubclassEnforcer)(GameObject*);
		//Tracking string for current context
		std::string currentContext;
	};

	/// \example Examples/ExampleGameData.cpp
	/// Demonstrates use of the various methods and important concepts of the GameData class.
}

#endif