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

	/// \brief All-static class with functions for handling a collection of Resource items.
	///
	/// The GameResources class is a class with all-static members which has a simple interface for adding/retrieving/deleting Resources
	/// from storage. This allows you to keep resources for your game (such as potentially large images, files etc) in a single location
	/// and then reference it via pointers to the resource so as to prevent duplication.
	/// Individual resources are identified by a string as its name.
	class GameResources
	{
	public:
		//Default Constructor
		GameResources();

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
		void AddResource(std::string name, Resource *newResource);
		/// \brief Gets the specified resource. Throws a ResourceNotFoundException if the resource does not exist.
		///
		/// \param name The name of the resource to retrieve.
		/// \return A pointer to the resource.
		Resource *GetResource(std::string name);
		/// \brief Gets the specified resource, cast to the specified Resource subclass. Will result in a std::bad_cast exception if
		/// the cast is invalid.
		///
		/// \param name The name of the resource to retrieve.
		/// \return A pointer to the resource, in the type specified.
		template <class T> T *GetResource(std::string name)
		{
			return dynamic_cast<T*>(GetResource(name));
		}
		/// \brief Deletes the specified resource. Throws a ResourceNotFoundException if the resource does not exist.
		///
		/// \param name The name of the resource to delete.
		/// \return void
		void DeleteResource(std::string name);

	private:
		//Typedef for our Resources storage
		typedef std::map<std::string, ResourcePointer> ResourceCollection;

		//Declare private properties
		//! Map storage for all our game resources
		ResourceCollection Resources;
	};
}

#endif