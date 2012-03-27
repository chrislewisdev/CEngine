/**************************************************
*CEngine
*Window.h by Chris Lewis
*Declaration for Window class
*Handles window creation and OpenGL setup
**************************************************/

//Include guard
#ifndef CENGINE_WINDOW_H
#define CENGINE_WINDOW_H

//Include any necessary headers
#include <stdexcept>

//Declare our class in the CEngine namespace
namespace CEngine
{
	class WINDOW
	{
	public:
		//Declare exception classes
		//Exception for initialisation errors e.g. MakeWindow and InitSDL
		class InitException : public std::exception
		{ 
		public:
			InitException(const char* what) : std::exception(what){};
		};

		//Constructor and Destructor
		WINDOW();
		~WINDOW();

		//Declare public functions
		//This function creates a window using SDL with the specified title, width and height
		void Open(const char *title, int width, int height);
		//This function will close our created window
		void Close();
		//This function sets our background colour using RGB values
		void SetBackgroundColour(float r, float g, float b);
		//This function flips our frame buffers
		void UpdateScreen();

	private:
		//Declare private functions
		//This function initialises SDL Video
		void InitSDL();

		//Declare private properties
		//Whether or not we've initialised SDL, and if we have a window open or not
		bool initialised, isOpen;
		//Width/height storage
		int width, height;
	};
}

#endif