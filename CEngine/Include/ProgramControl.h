/*******************************************************************
*CEngine
*ProgramControl.h by Chris Lewis
*Declares ProgramControl class for managing overall program flow
*******************************************************************/

#ifndef CENGINE_PROGRAMCONTROL_H
#define CENGINE_PROGRAMCONTROL_H

#include "Window.h"
#include "Input.h"
#include "GameControl.h"
#include "StateMachine.h"

namespace CEngine
{
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

		//Declare public properties
		//! Global access to our program's input- can only access const members like GetKey() and so on
		static const *Input ProgramInput;

	private:
		//Declare private properties
		//Input storage for our entire program
		static Input InputControl;
	};
}

#endif