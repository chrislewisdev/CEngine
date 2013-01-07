/*******************************************************************
*CEngine
*ProgramControl.h by Chris Lewis
*Declares ProgramControl class for managing overall program flow
*******************************************************************/

#ifndef CENGINE_PROGRAMCONTROL_H
#define CENGINE_PROGRAMCONTROL_H

#include "Window.h"
#include "Input.h"
#include "StateMachine.h"
#include "GameData.h"
#include "GameResources.h"

namespace CEngine
{
	/// \brief Singleton class to manage program flow and key game classes like GameStates and GameData. Used for running the main loop of your game.
	///
	/// The ProgramControl class is a singleton that brings the various key game component classes together to run your game. It acts as they key State Machine
	/// in your game and owns Game Data, the Game Control State Machine, InputManager and the Graphics Window. It should make up most of the necessary
	/// main loop for your game.
	///
	/// To use it correctly, you should instantiate ProgramControl in exactly one spot in your code to create the beginning instance (preferably at the very start
	/// of your application). Then use the static function Instance() to retrieve a reference to the Singleton instance, from where you can
	/// access key classes such as GameData.
	class ProgramControl : public StateMachine
	{
	public:
		/// \brief Main Constructor for the class. Takes the parameters required for Window::Open as it automatically opens a graphics window
		/// upon creation.
		///
		/// \param title Title for your graphics window.
		/// \param width The width for your graphics window.
		/// \param height The height for your graphics window.
		ProgramControl(const char *title, int width, int height);
		/// \brief Default Constructor. This one does not open a graphics window- ideal if you want to run a game simulation without graphics
		/// (e.g. tests).
		ProgramControl();
		/// \brief Destructor. Cleans up the singleton instance pointer.
		~ProgramControl();

		//Declare exception classes
		/// \brief Exception class for when the user tries to violate the singleton nature of ProgramControl.
		class SingletonViolationException : public std::exception
		{
		public:
			SingletonViolationException(const char *what) : std::exception(what) {}
		};

		//Declare public functions
		/// \brief Retrieve the singleton instance of ProgramControl.
		/// 
		/// \return A reference to a ProgramControl instance.
		static ProgramControl& Instance();
		/// \brief Updates our program State. In addition to updating whatever the current state is, performs other program tasks like updating
		/// processing event messages for input and so on.
		///
		/// \param deltaTime The time in seconds since the last update.
		/// \return void
		void Update(float deltaTime);
		/// \brief Returns the time that has passed since our last update in seconds.
		///
		/// \return Time in seconds as a float value.
		float TimeSinceLastUpdate() const;
		/// \brief Returns a pointer to our GameData storage instance.
		///
		/// \return A non-const pointer our Game Data. Use responsibly!
		GameData *GetGameData();
		/// \brief Returns a pointer to our Window instance.
		///
		/// \return A non-const pointer to our Window.
		Window *GetWindow();
		//// \brief Checks whether or not our application is trying to exit.
		///
		/// \return True if the program is trying to exit and should be terminated. False if not.
		bool IsExiting() const;
		/// \brief Sets whether or not the application will pause when minimised. (i.e. no game updates will be performed while paused)
		/// Set to false by default.
		///
		/// \param pause True to enable pausing, false to disable.
		void SetPauseOnMinimise(bool pause);

		//Declare public properties
		//! Global access to game resources
		GameResources& Resources;
		//! Global access to our program's input- can only access const members like GetKey() and so on
		const InputManager& Input;

	private:
		//! Declare copy constructor and assignment operator as private. For various reasons these are not feasible just now
		//! and most likely won't be needed.
		ProgramControl(const ProgramControl& other) : Input(InputControl), Resources(ResourcesControl) {}
		void operator = (const ProgramControl& other) {}

		//Declare private properties
		//! InputManager storage for our entire program
		InputManager InputControl;
		//! Our program's Window Instance
		Window MainWindow;
		//! Instance of our complete game data storage
		GameData Storage;
		//! Instance of GameResources
		GameResources ResourcesControl;
		//! Ticks counter- set in Update() and used by TimeSinceLastUpdate()
		unsigned int ticks;
		//! Exit flag- set to true when we want to exit the game
		bool exit;
		//! Flag for when the program is active (i.e. not minimised)
		bool active, pauseWhenInactive, inputFocus;

		//Declare private properties
		//! Our private singleton pointer
		static ProgramControl *instance;
	};

	/// \example Examples/ExampleProgramControl.cpp
	/// Demonstrates use of the ProgramControl class.
}

#endif