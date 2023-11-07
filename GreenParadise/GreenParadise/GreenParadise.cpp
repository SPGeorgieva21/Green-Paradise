#include <iostream>
#include "functions.h"

int main()
{
	switch (resolutionSettings())
	{
		case 1: gameMenu1280x720(); break;
		case 2: gameRes1980x1080(); break;
		default: std::cout << "Error => INCORRECT INPUT." << std::endl << "Closing game...";
	}
}