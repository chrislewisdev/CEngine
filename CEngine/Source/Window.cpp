/**************************************************
*CEngine
*Window.cpp by Chris Lewis
*Implements Window class
**************************************************/

//Include necessary headers
#include "Window.h"
#include <Windows.h>
#include <SDL.h>
#include <gl/GL.h>
#include <gl/GLAux.h>
#include <gl/GLU.h>
#include <gl/glext.h>

using namespace CEngine;

//Define our Constructor
Window::Window()
	: width(0), height(0), initialised(false), isOpen(false)
{
	
}

//Define our Destructor
Window::~Window()
{
	//Close our window in case it it's still open
	Close();
}

//This function creates a new SDL window with the specified title, width and height
void Window::Open(const char *title, int width, int height)
{
	//If our window is already open, exit
	if (isOpen) return;
	//If we haven't already initialised SDL, do so
	if (!initialised) InitSDL();

	//Try to retrieve video device info
	const SDL_VideoInfo *videoInfo = SDL_GetVideoInfo();
	if (!videoInfo)
	{
		SDL_Quit();
		initialised = false;
		throw InitException("Failed to retrieve video device info.");
	}

	//Set the title of our window
	SDL_WM_SetCaption(title, NULL);

	//Specify default OpenGL attributes
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Try set our video mode
	if (!SDL_SetVideoMode(width, height, videoInfo->vfmt->BitsPerPixel, SDL_OPENGL))
	{
		SDL_Quit();
		initialised = false;
		throw InitException("Failed to set video mode.");
	}

	//Set up Smooth Shading and a black background
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//Set up our on-screen viewport with our screen area sizes
	glViewport(0, 0, width, height);

	//Set up our projection matrix for a 2D projection with our pixel ends set for width/height
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, 0, 1);

	//Switch to and reset the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	isOpen = true;
}

//This function will close our owned window
void Window::Close()
{
	if (!isOpen) return;
	SDL_Quit();
	initialised = false;
	isOpen = false;
}

//This function sets our background colour using RGB values
void Window::SetBackgroundColour(float r, float g, float b)
{
	if (!isOpen) throw UsageException("Window must be Open before you set the background colour.");
	glClearColor(r, g, b, 1.0f);
}

//This function flips our frame buffers
void Window::UpdateScreen()
{
	if (!isOpen) throw UsageException("Window must be Open before you Update the screen.");
	SDL_GL_SwapBuffers();
}

//This function clears the current OpenGL screen
void Window::ClearScreen()
{
	if (!isOpen) throw UsageException("Window must be Open before you Clear the screen.");
	glClear(GL_COLOR_BUFFER_BIT);
}

//This function attempts to initialise SDL Video
void Window::InitSDL()
{
	//Check if SDL has already been initialised- this should mean another Window is already open
	if (SDL_WasInit(SDL_INIT_VIDEO) != 0)
	{
		throw InitException("SDL is already initialised. This most likely means another Window is already open. You cannot create multiple windows at the same time.");
	}
	//Check if ANYTHING has been initialised yet- if it has, we need only initialise the video subsystem
	if (SDL_WasInit(SDL_INIT_EVERYTHING) != 0)
	{
		if (SDL_InitSubSystem(SDL_INIT_VIDEO) == -1)
		{
			throw InitException("SDL Initialisation failed.");
		}
	}
	else
	{
		//Otherwise, do a normal Init for video only
		if (SDL_Init(SDL_INIT_VIDEO) == -1)
		{
			throw InitException("SDL Initialisation failed.");
		}
	}
	initialised = true;
}