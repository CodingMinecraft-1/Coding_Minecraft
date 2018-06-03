// The include statements, always include
// the header file specific to this .cpp file
// at the end.
#include <iostream>
#include <string>
#include <windows.h>
#include "Guess_My_Number.h"

// A well coded game will include a game loop.
// This is where execution of the game begins
// and it is also where the game terminates.
void Guess_My_Number::Begin_Game_Loop()
{
	std::string userIn;
	do {
		std::cout << "Would you like to play a game(Y/N)? " << std::endl;
		std::getline(std::cin, userIn);

		if(userIn.compare("Y") == 0)
			Play_Game();
	} while (userIn.compare("Y") == 0);

	// This is important because it pauses the program's
	// execution at the end of the game. It is not necessary
	// in this game, but gives the user more control.
	system("pause");
}

// This function is where the entire game 
// and logic is coded.
void Guess_My_Number::Play_Game() 
{
	// Introduce the user to the game.
	std::cout << "Guess a number between 1 and 1 000 000 and I will guess your number." << std::endl;
	Sleep(1000);
	std::cout << "Ready?" << std::endl;
	for (int i = 3; i > 0; i--) 
	{
		Sleep(1000);
		std::cout << i << std::endl;
	}
	std::cout << "Go!" << std::endl;

	// Initialize our main variables. 
	// NOTE: This could have also been done
	// in the header file.
	int low = 0;
	int high = 1000000;
	int mid = high / 2;
	std::string userIn = "";

	// This is where the game logic occurs, the
	// loop continues until the user indicates that
	// the computer has guessed correctly. The methodology
	// the computer uses is a binary search function.
	while (userIn.compare("C") != 0) 
	{
		std::cout << "\n\nI guess " << mid << std::endl;
		std::cout << "Type H for higher, L for lower, or C for correct." << std::endl;
		std::getline(std::cin, userIn);

		if (userIn.compare("H") == 0) 
		{
			low = mid;
		}
		else if (userIn.compare("L") == 0) 
		{
			high = mid;
		}
		else if (userIn.compare("C") != 0) 
		{
			std::cout << "Please input H, L, or C." << std::endl;
		}
		mid = (high + low) / 2;
	}
}

// Every C++ file needs a main function.
// This main function creates a Guess_My_Number
// class and executes the game loop function.
int main()
{
	Guess_My_Number* game = new Guess_My_Number();
	game->Begin_Game_Loop();
	return 0;
}