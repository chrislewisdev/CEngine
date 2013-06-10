/***********************************************************
*CEngine
*GameObjectHandle.h by Chris Lewis
*Defines the GameObjectHandle class, a weak reference to a GameObjectInstance with existence checking
***********************************************************/

#ifndef GAMEOBJECTHANDLE_H
#define GAMEOBJECTHANDLE_H

#include "GameObjectInstance.h"
#include <boost/weak_ptr.hpp>

namespace CEngine
{
	/// \brief The GameObjectHandle class acts as a weak reference to an existing GameObjectInstance; this can be passed around
	/// your game to access objects without having to copy GameObjectInstances around (which is not allowed). Existence checking is
	/// provided to make sure that the object you're accessing as actually still valid.
	class GameObjectHandle
	{
	public:
		GameObjectHandle();
		GameObjectHandle(GameObjectInstance &inst);

		//Declare a cast-to-bool operator
		operator bool ();
		//Declare pointer-like operators to access our actual GameObject instance
		GameObject *operator -> () const;
		//Declare assignment operator such that handles can be assigned to each other and from instances
		const GameObjectHandle& operator = (const GameObjectHandle& rhs)
		{
			reference = rhs.reference;
			return *this;
		}
		const GameObjectHandle& operator = (const GameObjectInstance& rhs)
		{
			reference = rhs.instance;
			return *this;
		}

	private:
		//Declare private properties
		//Weak pointer used for checking existence of our shared pointer
		boost::weak_ptr<GameObject> reference;
	};
}

#endif