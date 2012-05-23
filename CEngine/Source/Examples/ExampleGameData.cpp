#include <iostream>
#include "ProgramControl.h"

using namespace CEngine;
using namespace std;

//SDL defines a main symbol as SDL_main- to use a typical main we must undef this symbol
#undef main

int main()
{
	//Declare a ProgramControl instance as it houses our Game Data
	ProgramControl Control;

	return 0;
}