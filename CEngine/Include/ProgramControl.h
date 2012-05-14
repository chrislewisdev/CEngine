/*******************************************************************
*CEngine
*ProgramControl.h by Chris Lewis
*Declares ProgramControl class for managing overall program flow
*******************************************************************/

#ifndef CENGINE_PROGRAMCONTROL_H
#define CENGINE_PROGRAMCONTROL_H

#include <Windows.h>
#include "Window.h"
#include "Input.h"
#include "StateMachine.h"
#include "GameData.h"

namespace CEngine
{
	class GameData;

	/// \brief Manages program flow and key game classes like GameControl and GameData. Used for running the main loop of your game.
	///
	/// The ProgramControl class brings the various key game component classes together to run your game. It acts as they key State Machine
	/// in your game and owns Game Data, the Game Control State Machine, Input and the Graphics Window. It should make up most of the necessary
	/// main loop for your game.
	class ProgramControl : public StateMachine
	{
	public:
		/// \brief Single Constructor for the class. Takes the parameters required for Window::Open as it automatically opens a graphics window
		/// upon creation.
		///
		/// \param title Title for your graphics window.
		/// \param width The width for your graphics window.
		/// \param height The height for your graphics window.
		ProgramControl(const char *title, int width, int height);

		//Declare public functions
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

		//Declare public properties
		//! Global access to our program's input- can only access const members like GetKey() and so on
		static const Input const *ProgramInput;

	private:
		//Declare private properties
		//Input storage for our entire program
		static Input InputControl;
		//Our program's Window Instance
		Window MainWindow;
		//Instance of our complete game data storage
		GameData Storage;
		//Ticks counter- set in Update() and used by TimeSinceLastUpdate()
		DWORD ticks;
		//Exit flag- set to true when we want to exit the game
		bool exit;
	};
}

#endif