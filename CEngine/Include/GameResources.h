/*******************************************************************
*CEngine
*GameResources.h by Chris Lewis
*Static class used for containing global game resources
*******************************************************************/

#ifndef CENGINE_GAMERESOURCES_H
#define CENGINE_GAMERESOURCES_H

#include "Resource.h"
#include <map>
#include <boost/shared_ptr.hpp>

namespace CEngine
{
	/// \class CEngine::ResourcePointer
	/// \brief Alias as boost::shared_ptr<Resource>. Primarily used internally by class GameResources.
	typedef boost::shared_ptr<Resource> ResourcePointer;

	class GameResources
	{
	public:
		//Declare exception classes
		/// \brief Exception class for when a non-existent resource name is passed to GetResource.
		class ResourceNotFoundException : public std::exception
		{
		public:
			ResourceNotFoundException(const char *what) : std::exception(what) {}
		};

		//Declare public functions
		/// \brief Adds a new resource into our storage, with the supplied name.
		///
		/// \param name The name to use for the new resource.
		/// \param newResource Pointer to a new resource to take into our storage. The class will assume ownership of this pointer.
		/// \return void
		static void AddResource(std::string name, Resource *newResource);
		/// \brief Gets the specified resource.
		///
		/// \param name The name of the resource to retrieve.
		/// \return A pointer to the resource.
		static Resource *GetResource(std::string name);

	private:
		//Typedef for our Resources storage
		typedef std::map<std::string, ResourcePointer> ResourceCollection;

		//Declare private properties
		//! Map storage for all our game resources
		static ResourceCollection Resources;
	};
}

#endif