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
	/// These are typically expected to be external game files (e.g. images), hence the filename parameter in the Constructor.
	/// The filename is expected to be constant throughout a resource's lifetime, so it is declared private with the Filename() function
	/// used for retrieving it when necessary.
	/// It is strongly suggested you implement RAII (Resource Allocation Is Initialization) in your implementations of Resource-
	/// load your resource completely in the Constructor, and then clean up in the Destructor.
	class Resource
	{
	public:
		//! Constructor takes a single filename to use when loading.
		Resource(std::string fname) : filename(fname) {}
		//! Virtual destructor for polymorphism
		virtual ~Resource() = 0 {};

		//Declare public functions
		/// \brief Returns the filename of this resource
		/// \return The filename!
		const std::string& Filename() const {return filename;}

	private:
		//Declare private properties
		//! Filename used for this resource.
		std::string filename;
	};
}

#endif