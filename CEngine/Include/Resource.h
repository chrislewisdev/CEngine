/******************************************************************
*CEngine
*Resource.h by Chris Lewis
*Abstract class specifying interface for Game Resources
******************************************************************/

#ifndef CENGINE_RESOURCE_H
#define CENGINE_RESOURCE_H

#include <string>

namespace CEngine
{
	/// \brief Abstract class used to provide a common interface for game resources.
	///
	/// The Resource class defines a very simple interface for creating and loading game resources, which is used by the GameResources class.
	/// When creating any custom resource types for your game, inherit off this class and simply implement the Load function as necessary.
	class Resource
	{
	public:
		//! Constructor takes a single filename to use when loading.
		Resource(std::string fname) : filename(fname) {}

		//Declare public functions
		/// \brief Pure virtual function to implement loading of our resource. Use this to do whatever setup is required for your resource.
		/// \return void
		virtual void Load() = 0;

	private:
		//Declare private properties
		//! Filename used for this resource.
		std::string filename;
	};
}

#endif